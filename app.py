import json
from flask import Flask, render_template, request, redirect, url_for, flash
from sqlalchemy import func
from config import Config
from models import db, BusinessProfile, ProjectCaseStudy, ContentBrief, BlogPost, AgentRun, NicheOpportunity, TopicCluster, Campaign
from agents.content_pipeline_agent import ContentPipelineAgent
from agents.wordpress_draft_agent import WordPressDraftAgent
from datetime import datetime

app = Flask(__name__)
app.config.from_object(Config)
db.init_app(app)


def parse_json(value, default):
    try:
        return json.loads(value) if value else default
    except Exception:
        return default


def seed_demo_data():
    names = {b.name for b in BusinessProfile.query.all()}
    seed_profiles = [
        ("Social Club Pro", "Schedule a demo", ["/schedule-demo", "/membership-management"], ["American Legion membership software", "VFW membership software", "club website builder for social clubs", "membership renewal reminders for private clubs", "software for Moose Lodges", "private club email marketing software", "how to reduce paperwork for social clubs"]),
        ("Club Raffle Pro", "Schedule a demo", ["/schedule-demo", "/raffle-software"], ["raffle software for VFW", "raffle software for American Legion", "how to run a sweepstakes for a nonprofit", "online raffle software for clubs", "fundraising raffle ideas for fire departments", "how to sell more raffle tickets online", "raffle prize ideas for clubs"]),
        ("The TV Sign", "Get a signage demo", ["/schedule-demo", "/digital-signage-for-clubs"], ["digital signage for firemen’s clubs", "digital signage for VFW halls", "how clubs can sell TV sponsor ads", "TV advertising for local businesses", "digital signage for social clubs", "how to promote events on club TVs", "restaurant digital signage for daily specials"]),
    ]
    for name, cta, pages, kws in seed_profiles:
        if name in names:
            continue
        b = BusinessProfile(name=name, main_cta=cta, traffic_goal="Get demo requests from niche search traffic.", money_pages_json=json.dumps(pages), primary_keywords_json=json.dumps(kws), core_topics_json=json.dumps(kws[:3]))
        db.session.add(b)
        db.session.flush()
        db.session.add(ProjectCaseStudy(business_id=b.id, campaign=f"{name} Launch", project_name=f"SEO system for {name}", problem_solved="Low organic traffic", system_built="Niche SEO workflow", result="More qualified traffic", target_reader="Operators"))
        for q in kws:
            db.session.add(NicheOpportunity(business_id=b.id, campaign=f"{name} Launch", query=q, recommended_title=f"{q.title()}: Practical Guide", post_type="Software Use Case", search_intent="commercial", buyer_stage="solution_aware", target_money_page=pages[0], business_value_score=9, ranking_opportunity_score=7, why_it_can_win="Specific long-tail query tied to conversion.", content_angle=f"Use real examples for {q}.", cta=cta, status="idea"))
        db.session.add(TopicCluster(business_id=b.id, money_page=pages[0], cluster_name=f"{name} Core Cluster", pillar_topic=pages[0].strip('/').replace('-', ' '), supporting_posts_json=json.dumps(kws[:7])))
    db.session.commit()

    # Seed campaigns (idempotent)
    campaign_defs = [
        ("Club Raffle Pro", "Club Raffle Pro VFW Traffic Push", "Drive qualified traffic from VFWs looking for raffle and fundraiser software.", "/raffle-software", "raffle software for VFW", "VFW officers, fundraising chairs, and club managers", "VFW Raffle Planning Checklist", "Schedule a demo", "active"),
        ("Social Club Pro", "Social Club Pro Membership Growth Push", "Drive demo requests from clubs looking to modernize membership renewals and reduce paperwork.", "/membership-management", "American Legion membership software", "American Legion officers, VFW managers, Moose Lodge leaders, and private club boards", "Club Membership Renewal Checklist", "Schedule a demo", "active"),
        ("The TV Sign", "The TV Sign Sponsor Revenue Push", "Drive leads from clubs and local businesses interested in promoting sponsors, events, and specials on TV screens.", "/digital-signage-for-clubs", "how clubs can sell TV sponsor ads", "club managers, bar owners, restaurant operators, and local business owners", "TV Sponsor Ad Rate Sheet Template", "Get a signage demo", "active"),
    ]
    existing_campaigns = {c.name for c in Campaign.query.all()}
    for biz_name, name, goal, page, kw, audience, magnet, cta, status in campaign_defs:
        if name in existing_campaigns:
            continue
        biz = BusinessProfile.query.filter_by(name=biz_name).first()
        if biz:
            db.session.add(Campaign(business_id=biz.id, name=name, goal=goal, target_money_page=page, primary_keyword=kw, audience=audience, lead_magnet_idea=magnet, primary_cta=cta, status=status))
    db.session.commit()


@app.route('/')
def dashboard():
    top = NicheOpportunity.query.order_by(NicheOpportunity.business_value_score.desc(), NicheOpportunity.ranking_opportunity_score.desc()).limit(5).all()
    next_best = BlogPost.query.order_by(BlogPost.lead_readiness_score.desc().nullslast(), BlogPost.business_value_score.desc().nullslast()).first()
    return render_template('dashboard.html', total_business_profiles=BusinessProfile.query.count(), total_niche_opportunities=NicheOpportunity.query.count(), total_campaigns=Campaign.query.count(), total_agent_runs=AgentRun.query.count(), drafts=BlogPost.query.count(), high_priority=BlogPost.query.filter(BlogPost.publish_priority == 'high').count(), ready_review=BlogPost.query.filter(BlogPost.pipeline_status == 'needs_human_review').count(), by_status=db.session.query(BlogPost.pipeline_status, func.count(BlogPost.id)).group_by(BlogPost.pipeline_status).all(), niche_top=top, topic_clusters=TopicCluster.query.count(), missing_cta=BlogPost.query.filter((BlogPost.primary_cta == None) | (BlogPost.primary_cta == '')).count(), missing_money=BlogPost.query.filter((BlogPost.target_money_page == None) | (BlogPost.target_money_page == '')).count(), missing_links=BlogPost.query.filter((BlogPost.internal_links_json == None) | (BlogPost.internal_links_json == '[]')).count(), repurpose_ready=BlogPost.query.filter(BlogPost.repurposing_json != None).count(), highest_lead_score=db.session.query(func.max(BlogPost.lead_readiness_score)).scalar() or 0, next_best=next_best, lead_magnets=BlogPost.query.filter(BlogPost.lead_magnet_json != None).count(), money_pages_needing_support=BusinessProfile.query.count(), recent_drafts=BlogPost.query.order_by(BlogPost.created_at.desc()).limit(5).all(), recent_runs=AgentRun.query.order_by(AgentRun.started_at.desc()).limit(5).all(), active_campaigns=Campaign.query.filter_by(status='active').all())


@app.route('/seed-demo-data', methods=['POST'])
def seed_demo_data_route():
    seed_demo_data()
    flash('Demo data seeded (idempotent).', 'success')
    return redirect(url_for('dashboard'))


@app.route('/business-profiles')
def business_profiles():
    return render_template('business_profiles.html', items=BusinessProfile.query.all())


@app.route('/business-profiles/new', methods=['GET', 'POST'])
def new_business_profile():
    if request.method == 'POST':
        b = BusinessProfile(name=request.form.get('name', '').strip() or 'Untitled Business', website_url=request.form.get('website_url'), audience=request.form.get('audience'), offer=request.form.get('offer'), brand_voice=request.form.get('brand_voice'), main_cta=request.form.get('main_cta'), traffic_goal=request.form.get('traffic_goal'), core_topics_json=request.form.get('core_topics_json') or '[]', money_pages_json=request.form.get('money_pages_json') or '[]', primary_keywords_json=request.form.get('primary_keywords_json') or '[]', competitors_json=request.form.get('competitors_json') or '[]')
        db.session.add(b)
        db.session.commit()
        flash('Business profile created.', 'success')
        return redirect(url_for('business_profile_detail', business_id=b.id))
    return render_template('business_profile_form.html')


@app.route('/business-profiles/<int:business_id>')
def business_profile_detail(business_id):
    b = BusinessProfile.query.get_or_404(business_id)
    return render_template('business_profile_detail.html', b=b, topics=parse_json(b.core_topics_json, []), cases=ProjectCaseStudy.query.filter_by(business_id=b.id).all(), drafts=BlogPost.query.filter_by(business_id=b.id).all())


@app.route('/case-studies')
def case_studies(): return render_template('case_studies.html', items=ProjectCaseStudy.query.all())


@app.route('/case-studies/new', methods=['GET', 'POST'])
def new_case_study():
    businesses = BusinessProfile.query.all()
    if request.method == 'POST':
        cs = ProjectCaseStudy(business_id=int(request.form.get('business_id')), project_name=request.form.get('project_name') or 'Untitled Case Study', problem_solved=request.form.get('problem_solved'), system_built=request.form.get('system_built'), result=request.form.get('result'), target_reader=request.form.get('target_reader'), real_examples=request.form.get('real_examples'), screenshots_needed=request.form.get('screenshots_needed'), proof_points=request.form.get('proof_points'), lessons_learned=request.form.get('lessons_learned'), what_we_would_improve=request.form.get('what_we_would_improve'), campaign=request.form.get('campaign'))
        db.session.add(cs)
        db.session.commit()
        flash('Case study created.', 'success')
        return redirect(url_for('case_study_detail', case_id=cs.id))
    return render_template('case_study_form.html', businesses=businesses)


@app.route('/case-studies/<int:case_id>')
def case_study_detail(case_id): return render_template('case_study_detail.html', cs=ProjectCaseStudy.query.get_or_404(case_id), brief=ContentBrief.query.filter_by(case_study_id=case_id).first(), post=BlogPost.query.filter_by(case_study_id=case_id).first(), runs=AgentRun.query.filter_by(case_study_id=case_id).all())


@app.route('/niche-opportunities')
def niche_opportunities(): return render_template('niche_opportunities.html', items=NicheOpportunity.query.order_by(NicheOpportunity.business_value_score.desc()).all())


@app.route('/niche-opportunities/<int:op_id>')
def niche_opportunity_detail(op_id): return render_template('niche_opportunity_detail.html', o=NicheOpportunity.query.get_or_404(op_id))


@app.route('/niche-opportunities/<int:op_id>/run', methods=['POST'])
def run_niche(op_id):
    o = NicheOpportunity.query.get_or_404(op_id)
    b = BusinessProfile.query.get_or_404(o.business_id)
    try:
        post = ContentPipelineAgent(b, niche_opportunity=o).run()
        o.status = 'draft_created'
        db.session.commit()
        flash('Pipeline completed from niche opportunity.', 'success')
        return redirect(url_for('draft_detail', draft_id=post.id))
    except Exception as exc:
        db.session.rollback()
        flash(f'Pipeline failed: {exc}', 'error')
        return redirect(url_for('niche_opportunity_detail', op_id=op_id))


@app.route('/case-studies/<int:case_id>/run', methods=['POST'])
def run_pipeline(case_id):
    cs = ProjectCaseStudy.query.get_or_404(case_id)
    try:
        post = ContentPipelineAgent(BusinessProfile.query.get_or_404(cs.business_id), cs).run()
        flash('Pipeline completed.', 'success')
        return redirect(url_for('draft_detail', draft_id=post.id))
    except Exception as exc:
        db.session.rollback()
        flash(f'Pipeline failed: {exc}', 'error')
        return redirect(url_for('case_study_detail', case_id=case_id))




@app.route('/campaigns')
def campaigns():
    return render_template('campaigns.html', items=Campaign.query.order_by(Campaign.created_at.desc()).all())


@app.route('/campaigns/new', methods=['GET', 'POST'])
def new_campaign():
    businesses = BusinessProfile.query.all()
    if request.method == 'POST':
        c = Campaign(business_id=int(request.form.get('business_id')), name=request.form.get('name') or 'New Campaign', goal=request.form.get('goal'), target_money_page=request.form.get('target_money_page'), primary_keyword=request.form.get('primary_keyword'), audience=request.form.get('audience'), lead_magnet_idea=request.form.get('lead_magnet_idea'), primary_cta=request.form.get('primary_cta'), status=request.form.get('status') or 'planning')
        db.session.add(c); db.session.commit()
        flash('Campaign created.', 'success')
        return redirect(url_for('campaign_detail', campaign_id=c.id))
    return render_template('campaign_form.html', businesses=businesses)


@app.route('/campaigns/<int:campaign_id>')
def campaign_detail(campaign_id):
    c = Campaign.query.get_or_404(campaign_id)
    return render_template('campaign_detail.html', c=c, opportunities=NicheOpportunity.query.filter_by(campaign_id=c.id).all(), drafts=BlogPost.query.filter_by(campaign_id=c.id).all())
@app.route('/drafts')
def drafts(): return render_template('drafts.html', items=BlogPost.query.all())


@app.route('/drafts/<int:draft_id>')
def draft_detail(draft_id):
    draft = BlogPost.query.get_or_404(draft_id)
    readiness = parse_json(draft.publish_readiness_json, {})
    return render_template('draft_detail.html', campaign=Campaign.query.get(draft.campaign_id) if draft.campaign_id else None, wp_ready=bool(app.config.get('WORDPRESS_BASE_URL') and app.config.get('WORDPRESS_USERNAME') and app.config.get('WORDPRESS_APP_PASSWORD')), d=draft, checklist=parse_json(draft.publish_checklist_json or draft.seo_publish_checklist_json, {}), claim_check=parse_json(draft.claim_check_json, {}), cta_plan=parse_json(draft.cta_plan_json, {}), link_plan=parse_json(draft.internal_link_plan_json, {}), repurposing=parse_json(draft.repurposing_json, {}), refresh_plan=parse_json(draft.refresh_plan_json, {}), lead_path=parse_json(draft.lead_path_json, {}), lead_magnet=parse_json(draft.lead_magnet_json, {}), money_align=parse_json(draft.money_page_alignment_json, {}), readiness=readiness, tracking=parse_json(draft.tracking_plan_json, {}), image_quality=parse_json(draft.image_quality_json, {}), real_assets=parse_json(draft.real_assets_needed_json, {}), article_style=readiness.get("article_style_guard", {}))




@app.route('/drafts/<int:draft_id>/send-wordpress', methods=['POST'])
def send_wordpress_draft(draft_id):
    draft = BlogPost.query.get_or_404(draft_id)
    missing = []
    if not draft.title: missing.append('title')
    if not (draft.edited_body_markdown or draft.body_markdown): missing.append('body content')
    if not draft.seo_title: missing.append('SEO title')
    if not draft.meta_description: missing.append('meta description')
    if not draft.target_money_page: missing.append('target money page')
    if not (draft.primary_cta or draft.cta_plan_json): missing.append('CTA')
    if missing:
        flash('Cannot send to WordPress. Missing: ' + ', '.join(missing), 'error')
        return redirect(url_for('draft_detail', draft_id=draft_id))
    style_guard = parse_json(draft.publish_readiness_json, {}).get("article_style_guard", {})
    if style_guard and not style_guard.get("approved_for_wordpress_draft"):
        flash("Warning: Article Style Guard did not fully approve this draft. Send for manual review before publishing.", "warning")
    out = WordPressDraftAgent(BusinessProfile.query.get_or_404(draft.business_id), None, draft).execute({'wp_config': {'base_url': app.config.get('WORDPRESS_BASE_URL',''), 'username': app.config.get('WORDPRESS_USERNAME',''), 'app_password': app.config.get('WORDPRESS_APP_PASSWORD','')}})
    if out.get('success'):
        draft.wordpress_post_id = out.get('wordpress_post_id')
        draft.wordpress_post_url = out.get('wordpress_post_url')
        draft.wordpress_edit_url = out.get('wordpress_edit_url')
        draft.wordpress_status = out.get('wordpress_status')
        draft.sent_to_wordpress_at = datetime.utcnow()
        db.session.commit()
        flash('Draft sent to WordPress successfully.', 'success')
    else:
        flash(out.get('error','WordPress send failed.'), 'error')
    return redirect(url_for('draft_detail', draft_id=draft_id))
@app.route('/agent-runs')
def agent_runs(): return render_template('agent_runs.html', items=AgentRun.query.order_by(AgentRun.started_at.desc()).all())


@app.route('/agent-runs/<int:run_id>')
def agent_run_detail(run_id):
    r = AgentRun.query.get_or_404(run_id)
    return render_template('agent_run_detail.html', r=r, input_obj=parse_json(r.input_json, {}), output_obj=parse_json(r.output_json, {}))


if __name__ == '__main__':
    with app.app_context():
        db.create_all()
        seed_demo_data()
    print('SEO Content Machine running at http://127.0.0.1:5000')
    app.run(debug=True)

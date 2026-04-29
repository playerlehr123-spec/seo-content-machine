import json
from flask import Flask, render_template, request, redirect, url_for, flash
from config import Config
from models import db, BusinessProfile, ProjectCaseStudy, ContentBrief, BlogPost, AgentRun
from agents.content_pipeline_agent import ContentPipelineAgent

app = Flask(__name__)
app.config.from_object(Config)
db.init_app(app)


def seed_demo_data():
    if BusinessProfile.query.count() > 0:
        return
    businesses = [
        BusinessProfile(name="Social Club Pro", website_url="https://socialclubpro.com", audience="Private social clubs, VFWs, American Legions, Moose Lodges, firemen's clubs, and club managers.", offer="All-in-one membership, website, email, renewals, donations, member engagement, and club management platform.", brand_voice="Clear, practical, sales-forward, not overly technical, written for older club managers and board members.", main_cta="Schedule a demo.", core_topics_json=json.dumps(["membership growth", "club websites", "club events"])),
        BusinessProfile(name="Club Raffle Pro", website_url="https://clubrafflepro.com", audience="Clubs, nonprofits, PTOs, firemen's clubs, VFWs, Legions, and fundraising organizations.", offer="Raffle and sweepstakes software for online fundraisers.", brand_voice="Practical, trustworthy, fundraising-focused, easy to understand.", main_cta="Run your first raffle.", core_topics_json=json.dumps(["raffle software", "fundraising ideas", "ticket sales"])),
        BusinessProfile(name="The TV Sign", website_url="https://thetvsign.com", audience="Clubs, restaurants, bars, venues, and local businesses.", offer="Digital signage to promote events, specials, sponsors, and announcements.", brand_voice="Direct, local-business friendly, revenue-focused.", main_cta="Get a signage demo.", core_topics_json=json.dumps(["digital signage", "event promotion", "sponsor ads"])),
    ]
    for b in businesses:
        db.session.add(b)
    db.session.commit()
    cases = [
        ProjectCaseStudy(business_id=businesses[0].id, project_name="AI SEO Command Center for Social Clubs", problem_solved="Most clubs have outdated websites and no repeatable SEO/content system.", system_built="A multi-agent SEO content workflow for club-focused pages and posts.", result="Expected to improve search visibility and turn traffic into demo requests.", target_reader="Club managers"),
        ProjectCaseStudy(business_id=businesses[1].id, project_name="AI Content Machine for Raffle Software", problem_solved="Raffle software needs content across fundraising intent.", system_built="A case-study SEO machine for fundraising posts and landing pages.", result="Expected to drive qualified traffic from clubs and nonprofits.", target_reader="Fundraising teams"),
        ProjectCaseStudy(business_id=businesses[2].id, project_name="AI Local SEO System for Digital Signage", problem_solved="Businesses do not realize TVs can generate sponsor revenue.", system_built="A local SEO content system for signage education and demand capture.", result="Expected to generate more demo requests and local leads.", target_reader="Local operators"),
    ]
    for c in cases:
        db.session.add(c)
    db.session.commit()


@app.route('/')
def dashboard():
    stats = {
        'businesses': BusinessProfile.query.count(),
        'case_studies': ProjectCaseStudy.query.count(),
        'drafts': BlogPost.query.count(),
        'agent_runs': AgentRun.query.count(),
    }
    recent_drafts = BlogPost.query.order_by(BlogPost.created_at.desc()).limit(5).all()
    recent_runs = AgentRun.query.order_by(AgentRun.started_at.desc()).limit(10).all()
    return render_template('dashboard.html', stats=stats, recent_drafts=recent_drafts, recent_runs=recent_runs)

@app.route('/business-profiles')
def business_profiles(): return render_template('business_profiles.html', items=BusinessProfile.query.order_by(BusinessProfile.created_at.desc()).all())

@app.route('/business-profiles/new', methods=['GET', 'POST'])
def new_business_profile():
    if request.method == 'POST':
        p = BusinessProfile(name=request.form['name'], website_url=request.form.get('website_url'), audience=request.form.get('audience'), offer=request.form.get('offer'), brand_voice=request.form.get('brand_voice'), main_cta=request.form.get('main_cta'), core_topics_json=request.form.get('core_topics_json', '[]'))
        db.session.add(p); db.session.commit(); return redirect(url_for('business_profiles'))
    return render_template('business_profile_form.html')

@app.route('/business-profiles/<int:business_id>')
def business_profile_detail(business_id):
    b = BusinessProfile.query.get_or_404(business_id)
    cases = ProjectCaseStudy.query.filter_by(business_id=business_id).all()
    drafts = BlogPost.query.filter_by(business_id=business_id).all()
    return render_template('business_profile_detail.html', b=b, cases=cases, drafts=drafts)

@app.route('/case-studies')
def case_studies(): return render_template('case_studies.html', items=ProjectCaseStudy.query.order_by(ProjectCaseStudy.created_at.desc()).all())

@app.route('/case-studies/new', methods=['GET', 'POST'])
def new_case_study():
    businesses = BusinessProfile.query.all()
    if request.method == 'POST':
        c = ProjectCaseStudy(business_id=request.form['business_id'], project_name=request.form['project_name'], problem_solved=request.form.get('problem_solved'), system_built=request.form.get('system_built'), tools_used=request.form.get('tools_used'), before_state=request.form.get('before_state'), after_state=request.form.get('after_state'), result=request.form.get('result'), target_reader=request.form.get('target_reader'), notes=request.form.get('notes'))
        db.session.add(c); db.session.commit(); return redirect(url_for('case_studies'))
    return render_template('case_study_form.html', businesses=businesses)

@app.route('/case-studies/<int:case_id>')
def case_study_detail(case_id):
    cs = ProjectCaseStudy.query.get_or_404(case_id)
    brief = ContentBrief.query.filter_by(case_study_id=case_id).order_by(ContentBrief.created_at.desc()).first()
    post = BlogPost.query.filter_by(case_study_id=case_id).order_by(BlogPost.created_at.desc()).first()
    runs = AgentRun.query.filter_by(case_study_id=case_id).order_by(AgentRun.started_at.desc()).all()
    return render_template('case_study_detail.html', cs=cs, brief=brief, post=post, runs=runs)

@app.route('/case-studies/<int:case_id>/run', methods=['POST'])
def run_pipeline(case_id):
    cs = ProjectCaseStudy.query.get_or_404(case_id)
    b = BusinessProfile.query.get_or_404(cs.business_id)
    try:
        post = ContentPipelineAgent(b, cs).run()
        flash(f'Pipeline completed. Draft #{post.id} created.', 'success')
    except Exception as e:
        flash(f'Pipeline failed: {e}', 'error')
    return redirect(url_for('case_study_detail', case_id=case_id))

@app.route('/drafts')
def drafts(): return render_template('drafts.html', items=BlogPost.query.order_by(BlogPost.updated_at.desc()).all())
@app.route('/drafts/<int:draft_id>')
def draft_detail(draft_id): return render_template('draft_detail.html', d=BlogPost.query.get_or_404(draft_id))
@app.route('/agent-runs')
def agent_runs(): return render_template('agent_runs.html', items=AgentRun.query.order_by(AgentRun.started_at.desc()).all())
@app.route('/agent-runs/<int:run_id>')
def agent_run_detail(run_id): return render_template('agent_run_detail.html', r=AgentRun.query.get_or_404(run_id))

if __name__ == '__main__':
    with app.app_context():
        db.create_all()
        seed_demo_data()
    app.run(debug=True)

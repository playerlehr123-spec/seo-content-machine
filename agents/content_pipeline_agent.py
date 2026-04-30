import json
from models import db, ContentBrief, BlogPost, TopicCluster
from agents.niche_opportunity_agent import NicheOpportunityAgent
from agents.topic_cluster_agent import TopicClusterAgent
from agents.search_intent_agent import SearchIntentAgent
from agents.serp_angle_agent import SERPAngleAgent
from agents.proof_injection_agent import ProofInjectionAgent
from agents.content_brief_agent import ContentBriefAgent
from agents.blog_writer_agent import BlogWriterAgent
from agents.editor_agent import EditorAgent
from agents.claim_check_agent import ClaimCheckAgent
from agents.seo_optimizer_agent import SEOOptimizerAgent
from agents.ai_search_answer_agent import AISearchAnswerAgent
from agents.internal_link_graph_agent import InternalLinkGraphAgent
from agents.conversion_path_agent import ConversionPathAgent
from agents.money_page_alignment_agent import MoneyPageAlignmentAgent
from agents.lead_path_agent import LeadPathAgent
from agents.lead_magnet_agent import LeadMagnetAgent
from agents.publish_readiness_agent import PublishReadinessAgent
from agents.tracking_plan_agent import TrackingPlanAgent
from agents.blog_card_image_agent import BlogCardImageAgent
from agents.image_quality_agent import ImageQualityAgent
from agents.publish_checklist_agent import PublishChecklistAgent
from agents.repurposing_agent import RepurposingAgent
from agents.refresh_planner_agent import RefreshPlannerAgent


class ContentPipelineAgent:
    def __init__(self, business, case_study=None, niche_opportunity=None):
        self.business = business
        self.case_study = case_study
        self.niche_opportunity = niche_opportunity

    def run(self):
        if self.niche_opportunity:
            opp = {k: getattr(self.niche_opportunity, k) for k in ["query", "recommended_title", "post_type", "search_intent", "buyer_stage", "target_money_page", "business_value_score", "ranking_opportunity_score", "why_it_can_win", "cta"]}
        else:
            opp = (NicheOpportunityAgent(self.business, self.case_study).execute({}).get("opportunities") or [{}])[0]
        cluster = TopicClusterAgent(self.business, self.case_study).execute({"money_page": opp.get("target_money_page")})
        intent = SearchIntentAgent(self.business, self.case_study).execute({"query": opp.get("query")})
        serp = SERPAngleAgent(self.business, self.case_study).execute({"query": opp.get("query"), "target_money_page": opp.get("target_money_page")})
        proof = ProofInjectionAgent(self.business, self.case_study).execute({})
        brief_out = ContentBriefAgent(self.business, self.case_study).execute({"opportunity": opp, "intent": intent, "serp_angle": serp, "proof": proof})
        db.session.add(TopicCluster(business_id=self.business.id, money_page=cluster.get("money_page"), cluster_name=cluster.get("cluster_name"), pillar_topic=cluster.get("pillar_topic"), supporting_posts_json=json.dumps(cluster.get("supporting_posts", []))))
        db.session.commit()
        brief = ContentBrief(business_id=self.business.id, case_study_id=self.case_study.id if self.case_study else None, target_keyword=brief_out.get("target_keyword"), search_intent=brief_out.get("search_intent"), target_money_page=brief_out.get("target_money_page"), post_type=brief_out.get("post_type"), buyer_stage=brief_out.get("buyer_stage"), title_options_json=json.dumps(brief_out.get("title_options", [])), selected_title=(brief_out.get("title_options") or [""])[0], h1=brief_out.get("h1"), outline_json=json.dumps(brief_out.get("outline", [])), faqs_json=json.dumps(brief_out.get("faqs", [])), cta=brief_out.get("cta"), internal_link_targets_json=json.dumps(brief_out.get("internal_link_targets", [])), meta_title=brief_out.get("meta_title"), meta_description=brief_out.get("meta_description"))
        db.session.add(brief); db.session.commit()
        draft = BlogWriterAgent(self.business, self.case_study).execute({"brief": brief_out, "proof": proof})
        post = BlogPost(business_id=self.business.id, case_study_id=self.case_study.id if self.case_study else None, content_brief_id=brief.id, title=draft.get("title"), slug=draft.get("slug"), body_markdown=draft.get("body_markdown"), pipeline_status="draft", target_keyword=brief_out.get("target_keyword"), search_intent=brief_out.get("search_intent"), buyer_stage=brief_out.get("buyer_stage"), post_type=brief_out.get("post_type"), target_money_page=brief_out.get("target_money_page"), business_value_score=opp.get("business_value_score", 8), ranking_opportunity_score=opp.get("ranking_opportunity_score", 7), campaign=(self.case_study.campaign if self.case_study else getattr(self.niche_opportunity, "campaign", "Default Campaign")))
        db.session.add(post); db.session.commit()
        edited = EditorAgent(self.business, self.case_study, post).execute({"draft": draft})
        claim = ClaimCheckAgent(self.business, self.case_study, post).execute({"body": edited.get("edited_body_markdown")})
        seo = SEOOptimizerAgent(self.business, self.case_study, post).execute({"title": post.title})
        ai = AISearchAnswerAgent(self.business, self.case_study, post).execute({"target_keyword": post.target_keyword, "search_intent": post.search_intent})
        links = InternalLinkGraphAgent(self.business, self.case_study, post).execute({"money_page": post.target_money_page, "cluster_name": cluster.get("cluster_name"), "keyword": post.target_keyword})
        conversion = ConversionPathAgent(self.business, self.case_study, post).execute({"target_money_page": post.target_money_page})
        alignment = MoneyPageAlignmentAgent(self.business, self.case_study, post).execute({"target_money_page": post.target_money_page, "target_keyword": post.target_keyword})
        lead_path = LeadPathAgent(self.business, self.case_study, post).execute({"target_keyword": post.target_keyword, "search_intent": post.search_intent, "buyer_stage": post.buyer_stage, "post_type": post.post_type, "target_money_page": post.target_money_page})
        lead_magnet = LeadMagnetAgent(self.business, self.case_study, post).execute({"lead_magnet_idea": lead_path.get("lead_magnet_idea")})
        readiness = PublishReadinessAgent(self.business, self.case_study, post).execute({"target_money_page": post.target_money_page, "primary_cta": lead_path.get("primary_cta"), "lead_magnet_title": lead_magnet.get("lead_magnet_title"), "has_internal_links": bool(links.get("links"))})
        tracking = TrackingPlanAgent(self.business, self.case_study, post).execute({"slug": post.slug})
        image = BlogCardImageAgent(self.business, self.case_study, post).execute({"topic": post.title})
        image_quality = ImageQualityAgent(self.business, self.case_study, post).execute({"image_prompt": image.get("image_prompt"), "image_brief": image.get("image_brief")})
        checklist = PublishChecklistAgent(self.business, self.case_study, post).execute({"force_missing": ["No unsupported claims"] if claim.get("flagged_claims") else []})
        repurpose = RepurposingAgent(self.business, self.case_study, post).execute({"title": post.title})
        refresh = RefreshPlannerAgent(self.business, self.case_study, post).execute({})
        post.edited_body_markdown = edited.get("edited_body_markdown")
        post.seo_title = seo.get("seo_title")
        post.meta_description = seo.get("meta_description")
        post.slug = seo.get("slug") or post.slug
        post.excerpt = seo.get("excerpt")
        post.category = seo.get("category")
        post.tags_json = json.dumps(seo.get("tags", []))
        post.ai_answer_block = ai.get("ai_answer_block")
        post.internal_link_plan_json = json.dumps(links)
        post.internal_links_json = json.dumps(links.get("links", []))
        post.cta_plan_json = json.dumps(conversion)
        post.claim_check_json = json.dumps(claim)
        post.publish_checklist_json = json.dumps(checklist)
        post.repurposing_json = json.dumps(repurpose)
        post.refresh_plan_json = json.dumps(refresh)
        post.money_page_alignment_json = json.dumps(alignment)
        post.lead_path_json = json.dumps(lead_path)
        post.lead_magnet_json = json.dumps(lead_magnet)
        post.publish_readiness_json = json.dumps(readiness)
        post.tracking_plan_json = json.dumps(tracking)
        post.conversion_goal = lead_path.get("conversion_goal")
        post.primary_cta = lead_path.get("primary_cta")
        post.secondary_cta = lead_path.get("secondary_cta")
        post.lead_readiness_score = readiness.get("lead_readiness_score")
        post.real_assets_needed_json = json.dumps(proof.get("real_assets_needed", {}))
        post.image_brief = image.get("image_brief")
        post.image_prompt = image.get("image_prompt")
        post.image_negative_prompt = image.get("negative_prompt")
        post.image_style_notes = image.get("style_notes")
        post.recommended_image_type = image.get("recommended_image_type")
        post.image_alt_text = image.get("alt_text")
        post.image_quality_json = json.dumps(image_quality)
        post.publish_priority = "high" if (post.business_value_score or 0) >= 8 else "medium"
        gate_checks = {
            "cta_exists": bool(post.primary_cta),
            "money_page_exists": bool(post.target_money_page),
            "claim_check_passed": len(claim.get("flagged_claims", [])) == 0,
            "image_quality_reviewed": bool(image_quality.get("human_review_required")),
            "internal_links_exist": bool(links.get("links")),
            "human_review_checked": False,
        }
        if not all([gate_checks["cta_exists"], gate_checks["money_page_exists"], gate_checks["internal_links_exist"]]):
            post.pipeline_status = "not_ready"
        elif gate_checks["claim_check_passed"] and checklist.get("ready_to_publish") and readiness.get("ready_for_review"):
            post.pipeline_status = "needs_human_review"
        else:
            post.pipeline_status = "needs_refresh"
        db.session.commit()
        return post

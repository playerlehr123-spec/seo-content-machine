import json
from agents.base import BaseAgent


class ContentBriefAgent(BaseAgent):
    name = "ContentBriefAgent"
    description = "Builds detailed brief from opportunity + intent + SERP angle"

    def run(self, input_data):
        opp = input_data.get("opportunity", {})
        intent = input_data.get("intent", {})
        angle = input_data.get("serp_angle", {})
        pages = json.loads(self.business.money_pages_json or "[]")
        target_money_page = opp.get("target_money_page") or (pages[0] if pages else "/schedule-demo")
        if self.business.name == "The TV Sign":
            target_money_page = "/contact-us"
        keyword = opp.get("query") or input_data.get("query") or (self.case_study.project_name if self.case_study else "")
        title = opp.get("recommended_title") or f"{keyword.title()}: Practical Guide"
        faqs = intent.get("must_answer_questions", ["What should readers do next?"])[:3]
        return {
            "target_keyword": keyword,
            "search_intent": intent.get("search_intent", opp.get("search_intent", "commercial")),
            "buyer_stage": intent.get("buyer_stage", opp.get("buyer_stage", "solution_aware")),
            "traffic_intent": "Drive qualified search traffic and route to money page",
            "post_type": intent.get("recommended_post_type", opp.get("post_type", "Software Use Case")),
            "target_reader": self.business.audience,
            "target_money_page": target_money_page,
            "cta": "Get a signage demo" if self.business.name == "The TV Sign" else (opp.get("cta") or self.business.main_cta),
            "title_options": [title],
            "h1": title,
            "quick_answer": f"{keyword} works best when you use existing screens to deliver clear offers, sponsor visibility, and event promotion with a direct CTA to {target_money_page}.",
            "outline": [{"heading": "Quick Answer", "subpoints": ["Answer in 2-4 sentences"]}, {"heading": "Problem", "subpoints": ["Why existing screens underperform"]}, {"heading": "How It Works", "subpoints": ["Simple repeatable workflow"]}, {"heading": "Use Case", "subpoints": [self.business.audience or "Operators"]}, {"heading": "Common Mistakes", "subpoints": angle.get("what_generic_posts_miss", [])}, {"heading": "FAQ", "subpoints": faqs}],
            "faqs": faqs,
            "internal_link_targets": [target_money_page],
            "suggested_schema_type": "Article",
            "meta_title": f"{title} | {self.business.name}",
            "meta_description": f"Human-reviewed guide for {keyword} with practical steps and CTA to {target_money_page}.",
            "why_this_can_drive_traffic": opp.get("why_it_can_win", "Specific long-tail query with clear intent")
        }

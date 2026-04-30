import json
from agents.base import BaseAgent


class NicheOpportunityAgent(BaseAgent):
    name = "NicheOpportunityAgent"
    description = "Generates niche long-tail SEO opportunities"

    def run(self, input_data):
        keywords = json.loads(self.business.primary_keywords_json or '[]')
        pages = json.loads(self.business.money_pages_json or '[]')
        cta = self.business.main_cta or "Schedule a demo"
        opportunities = []
        for i, kw in enumerate(keywords[:7]):
            opportunities.append({
                "query": kw,
                "recommended_title": f"{kw.title()}: Practical Guide for {self.business.name}",
                "post_type": "Software Use Case",
                "search_intent": "commercial",
                "buyer_stage": "solution_aware",
                "target_money_page": pages[min(i, len(pages)-1)] if pages else "/schedule-demo",
                "business_value_score": 9,
                "ranking_opportunity_score": 7,
                "why_it_can_win": "Long-tail phrase with clear problem-solution fit.",
                "content_angle": f"Show practical steps and examples for {kw}.",
                "cta": cta,
            })
        return {"opportunities": opportunities}

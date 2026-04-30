import json
from agents.base import BaseAgent


class MoneyPageAlignmentAgent(BaseAgent):
    name = "MoneyPageAlignmentAgent"
    description = "Aligns post with best-fit money page"

    def run(self, input_data):
        pages = json.loads(self.business.money_pages_json or "[]")
        target = input_data.get("target_money_page") or (pages[0] if pages else "/schedule-demo")
        return {
            "target_money_page": target,
            "supporting_money_pages": pages[1:3],
            "primary_anchor_text": input_data.get("target_keyword", "schedule a demo"),
            "secondary_anchor_texts": ["schedule a demo", "learn more"],
            "why_this_page_matches_intent": "Maps high-intent readers to the closest conversion page.",
            "cta_match_score": 9,
        }

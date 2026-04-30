from agents.base import BaseAgent


class EditorialCalendarAgent(BaseAgent):
    name = "EditorialCalendarAgent"
    description = "Recommends next posts and weekly plan"

    def run(self, input_data):
        opps = input_data.get("opportunities", [])
        rec = []
        for item in opps[:3]:
            rec.append({"query": item.get("query"), "title": item.get("recommended_title"), "reason": "High business value + conversion alignment", "priority": "high", "target_money_page": item.get("target_money_page")})
        return {"recommended_next_posts": rec, "weekly_plan": [r.get("title") for r in rec]}

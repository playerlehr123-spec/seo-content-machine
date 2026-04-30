from agents.base import BaseAgent


class RefreshPlannerAgent(BaseAgent):
    name = "RefreshPlannerAgent"
    description = "Creates placeholder refresh plan"

    def run(self, input_data):
        return {
            "check_again_in_days": 30,
            "signals_to_watch": ["impressions but low clicks", "ranking positions 8-20", "queries not covered in post", "no demo clicks"],
            "future_refresh_actions": ["Expand FAQ with new questions", "Strengthen CTA if clicks are weak"]
        }

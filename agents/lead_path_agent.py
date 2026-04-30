from agents.base import BaseAgent


class LeadPathAgent(BaseAgent):
    name = "LeadPathAgent"
    description = "Defines conversion path for each post"

    def run(self, input_data):
        topic = input_data.get("target_keyword", "this topic")
        page = input_data.get("target_money_page", "/schedule-demo")
        return {
            "conversion_goal": "schedule_demo",
            "primary_cta": self.business.main_cta or "Schedule a demo",
            "secondary_cta": "Download the checklist",
            "target_money_page": page,
            "lead_magnet_idea": f"{topic.title()} Checklist",
            "form_fields": ["name", "email", "organization", "role", "website"],
            "cta_placement_plan": ["soft CTA after Quick Answer", "strong CTA after Common Mistakes", "final CTA at bottom"],
            "follow_up_email_subject": f"Your {topic} checklist",
            "follow_up_email_body": "Thanks for requesting the checklist. Here is your next-step guide and demo link.",
            "conversion_notes": [],
        }

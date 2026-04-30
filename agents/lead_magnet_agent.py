from agents.base import BaseAgent


class LeadMagnetAgent(BaseAgent):
    name = "LeadMagnetAgent"
    description = "Suggests lead magnet per topic"

    def run(self, input_data):
        title = input_data.get("lead_magnet_idea") or "SEO Checklist"
        return {
            "lead_magnet_title": title,
            "lead_magnet_type": "checklist",
            "why_it_fits": "Simple, practical asset aligned to intent and conversion stage.",
            "outline": ["Preparation", "Execution", "Compliance check", "Next-step CTA"],
            "download_cta": "Download the checklist",
            "follow_up_offer": self.business.main_cta or "Schedule a demo",
        }

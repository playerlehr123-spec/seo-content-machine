from agents.base import BaseAgent


class ConversionCTAAgent(BaseAgent):
    name = "ConversionCTAAgent"
    description = "Builds conversion CTA plan"

    def run(self, input_data):
        money_page = input_data.get("target_money_page") or "/schedule-demo"
        primary = f"Visit {money_page}"
        return {
            "primary_cta": primary,
            "secondary_cta": "Request a walkthrough",
            "cta_placement_notes": ["Add CTA after Quick Answer", "Add CTA in final section"],
            "lead_magnet_idea": "One-page implementation checklist",
            "conversion_notes": ["Use audience-specific CTA copy", "Tie CTA to solved pain point"]
        }

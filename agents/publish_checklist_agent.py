from agents.base import BaseAgent


class PublishChecklistAgent(BaseAgent):
    name = "PublishChecklistAgent"
    description = "Human review checklist"

    def run(self, input_data):
        checklist = [
            "SEO title added", "Meta description added", "Slug reviewed", "Quick Answer included",
            "FAQ section included", "Internal links added", "CTA points to target money page",
            "Image alt text added", "Human reviewed for accuracy", "No unsupported claims"
        ]
        missing = [item for item in checklist if item in input_data.get("force_missing", [])]
        return {"checklist": checklist, "missing_items": missing, "ready_to_publish": len(missing) == 0}

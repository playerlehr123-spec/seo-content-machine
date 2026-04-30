from agents.base import BaseAgent


class PublishReadinessAgent(BaseAgent):
    name = "PublishReadinessAgent"
    description = "Checks if post is lead-ready"

    def run(self, input_data):
        checks = [
            {"item": "Target money page selected", "status": "pass" if input_data.get("target_money_page") else "fail", "note": ""},
            {"item": "CTA included", "status": "pass" if input_data.get("primary_cta") else "fail", "note": ""},
            {"item": "Lead magnet suggested", "status": "pass" if input_data.get("lead_magnet_title") else "fail", "note": ""},
            {"item": "Internal links included", "status": "pass" if input_data.get("has_internal_links") else "fail", "note": ""},
            {"item": "Human review required", "status": "pass", "note": "Manual review before publish"},
        ]
        missing = [c["item"] for c in checks if c["status"] == "fail"]
        score = int(((len(checks) - len(missing)) / len(checks)) * 10)
        return {"ready_for_review": len(missing) == 0, "lead_readiness_score": score, "checks": checks, "missing_items": missing}

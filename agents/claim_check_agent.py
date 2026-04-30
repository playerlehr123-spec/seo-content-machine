from agents.base import BaseAgent


class ClaimCheckAgent(BaseAgent):
    name = "ClaimCheckAgent"
    description = "Flags risky claims and adds compliance notes"

    def run(self, input_data):
        text = (input_data.get("body") or "").lower()
        flagged = []
        if "%" in text or "x" in text:
            flagged.append("Possible unsupported stat or performance claim")
        if "guarantee" in text:
            flagged.append("Revenue guarantee language")
        compliance = []
        if "raffle" in text or "sweepstakes" in text:
            compliance.append("Rules vary by location. Check state and local requirements before running a raffle or sweepstakes.")
        return {"flagged_claims": flagged, "safer_rewrites": ["Replace absolute claims with evidence-based phrasing"], "compliance_notes": compliance, "approval_required": True}

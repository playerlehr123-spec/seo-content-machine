from agents.base import BaseAgent


class ImageQualityAgent(BaseAgent):
    name = "ImageQualityAgent"
    description = "Scores and flags image brief quality before generation/publish"

    def run(self, input_data):
        prompt = (input_data.get("image_prompt") or "").lower()
        flags = []
        banned = ["robot", "cyberpunk", "neon", "futuristic clutter", "fake ui", "people", "faces"]
        for term in banned:
            if term in prompt:
                flags.append(f"Potential low-trust style: {term}")
        if "text" in prompt:
            flags.append("Risk of fake text in image")
        score = max(0, 10 - len(flags) * 2)
        return {
            "quality_score": score,
            "risk_flags": flags,
            "improvement_notes": ["Keep composition minimal", "Use real screenshot if possible", "Avoid misleading UI implications"],
            "approved_for_generation": score >= 7 and len(flags) == 0,
            "human_review_required": True,
        }

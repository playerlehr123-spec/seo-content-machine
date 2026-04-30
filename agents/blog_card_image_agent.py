from agents.base import BaseAgent


class BlogCardImageAgent(BaseAgent):
    name = "BlogCardImageAgent"
    description = "Creates high-trust image brief/prompt with strict quality rules"

    def run(self, input_data):
        topic = input_data.get("topic") or (self.case_study.project_name if self.case_study else "SEO workflow")
        return {
            "image_brief": f"Use existing approved brand assets for '{topic}' (no AI image generation).",
            "image_prompt": "Use existing screenshot or branded Canva-style asset from library. No new AI generation.",
            "negative_prompt": "No fake UI, no fake text, no distorted logos, no uncanny people.",
            "style_notes": "Use existing image assets only. Human review required.",
            "alt_text": f"Branded visual supporting {topic}",
            "recommended_image_type": "screenshot",
            "human_review_required": True,
        }

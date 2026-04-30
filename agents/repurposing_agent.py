from agents.base import BaseAgent


class RepurposingAgent(BaseAgent):
    name = "RepurposingAgent"
    description = "Repurposes draft into multi-channel assets"

    def run(self, input_data):
        title = input_data.get("title", "New post")
        return {
            "linkedin_post": f"We published: {title}. Here's the operator playbook and next step CTA.",
            "facebook_post": f"New practical guide: {title}.",
            "email_newsletter_blurb": f"This week: {title} and how to apply it.",
            "short_video_script": f"Hook: {title}. Step 1... Step 2... CTA.",
            "sales_email_angle": f"Use {title} as proof-based follow-up content.",
            "faq_snippets": ["What problem does this solve?", "What should readers do next?"]
        }

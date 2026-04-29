from agents.base import BaseAgent


class InternalLinkAgent(BaseAgent):
    name = "InternalLinkAgent"
    description = "Suggests internal links"

    def run(self, input_data):
        return {"links": [{"source": "new_blog_post", "target": "/services/ai-seo-systems", "anchor_text": "AI SEO systems", "reason": "Relevant money page for service-aware readers."}]}

from agents.base import BaseAgent
from services.seo_utils import slugify


class SEOOptimizerAgent(BaseAgent):
    name = "SEOOptimizerAgent"
    description = "Optimizes post for Google SEO"

    def run(self, input_data):
        title = input_data.get("title", "Untitled")
        return {
            "seo_title": f"{title} | {self.business.name}",
            "meta_description": "Practical, human-reviewed guide tied to a clear money page CTA.",
            "slug": slugify(title),
            "excerpt": "Useful, specific post designed for long-tail SEO traffic.",
            "category": "SEO Growth",
            "tags": ["seo", "long-tail", "ai search"],
            "heading_notes": ["Keep one H1", "Use descriptive H2s"],
            "seo_notes": ["Intent matched", "CTA mapped", "Internal links planned"]
        }

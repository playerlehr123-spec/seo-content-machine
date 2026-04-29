from agents.base import BaseAgent
from services.seo_utils import slugify


class SEOOptimizerAgent(BaseAgent):
    name = "SEOOptimizerAgent"
    description = "Creates SEO package"

    def run(self, input_data):
        title = input_data.get("title", self.case_study.project_name)
        return {"seo_title": f"{title} | SEO Content Machine", "meta_description": "Proof-based case study showing a practical multi-agent SEO workflow.", "slug": slugify(title), "excerpt": "A practical case study on building a proof-based SEO content workflow.", "category": "Case Studies", "tags": ["seo", "content systems", "case study"], "seo_notes": ["Primary keyword in title", "Clear user intent alignment"]}

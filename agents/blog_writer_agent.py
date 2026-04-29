from agents.base import BaseAgent
from services.seo_utils import slugify


class BlogWriterAgent(BaseAgent):
    name = "BlogWriterAgent"
    description = "Writes markdown draft"

    def run(self, input_data):
        brief = input_data.get("brief", {})
        title = brief.get("selected_title", self.case_study.project_name)
        body = f"# {title}\n\nWe built this system to solve a real delivery problem: {self.case_study.problem_solved}.\n\n## What we built\n{self.case_study.system_built}\n\n## How it works\nThe pipeline moves from case-study angle to brief, draft, edit, SEO packaging, and internal linking.\n\n## Practical takeaway\nUse one source of truth per project and let each agent transform that source without inventing claims.\n\n## CTA\n{self.business.main_cta or 'Book a call to see the workflow.'}"
        return {"title": title, "slug": slugify(title), "body_markdown": body}

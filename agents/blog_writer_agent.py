from agents.base import BaseAgent
from services.seo_utils import slugify


class BlogWriterAgent(BaseAgent):
    name = "BlogWriterAgent"
    description = "Writes markdown draft from brief"

    def run(self, input_data):
        brief = input_data.get("brief", {})
        title = brief.get("h1") or "Draft"
        problem = self.case_study.problem_solved if self.case_study and self.case_study.problem_solved else "Teams rely on manual workflows and inconsistent promotion."
        system = self.case_study.system_built if self.case_study and self.case_study.system_built else "A repeatable workflow tied to one conversion page."
        faq_items = brief.get("faqs", [])[:3]
        faq_lines = "\n".join([f"- {q}" for q in faq_items])
        cta = brief.get("cta") or self.business.main_cta
        money = brief.get("target_money_page")
        if self.business.name == "The TV Sign":
            cta = "Get a signage demo"
            money = "/contact-us"
        body = (
            f"# {title}\n\n"
            f"## Quick Answer\n{brief.get('quick_answer')}\n\n"
            f"## Problem\n{problem}\n\n"
            f"## How It Works\n{system}\n\n"
            "## Practical Example\nA local venue can rotate sponsor ads, event reminders, and weekly specials on existing screens to generate awareness and measurable response without buying new hardware.\n\n"
            "## Common Mistakes\n"
            "- Generic messaging with no clear offer\n"
            "- No CTA tied to one next step\n"
            "- No internal links to money pages\n\n"
            f"## FAQ\n{faq_lines}\n\n"
            f"## Internal Links\n- {money}\n\n"
            f"## CTA\n{cta} - {money}"
        )
        return {"title": title, "slug": slugify(title), "body_markdown": body}

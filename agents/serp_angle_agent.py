from agents.base import BaseAgent


class SERPAngleAgent(BaseAgent):
    name = "SERPAngleAgent"
    description = "Creates non-generic angle for likely SERP"

    def run(self, input_data):
        query = input_data.get("query", "this topic")
        return {
            "unique_angle": f"Field-tested workflow for {query} with audience-specific examples and conversion path.",
            "what_generic_posts_miss": ["No practical examples", "No audience-specific constraints", "No direct money-page CTA"],
            "original_examples_to_include": ["Before/after workflow", "Checklist used internally", "One real implementation caveat"],
            "sections_that_make_this_better": ["Quick Answer", "Best For", "Common Mistakes", "FAQ with conversion step"]
        }

from agents.base import BaseAgent


class ContentBriefAgent(BaseAgent):
    name = "ContentBriefAgent"
    description = "Creates SEO brief"

    def run(self, input_data):
        angle = input_data.get("angle", {})
        keyword = angle.get("target_keyword", self.case_study.project_name.lower())
        title = angle.get("title", self.case_study.project_name)
        outline = [
            {"heading": "The problem we needed to solve", "subpoints": [self.case_study.problem_solved or "Manual content process"]},
            {"heading": "Why the old way broke down", "subpoints": [self.case_study.before_state or "No repeatable system"]},
            {"heading": "The system we built", "subpoints": [self.case_study.system_built or "Multi-agent workflow"]},
            {"heading": "How each agent works", "subpoints": ["Angle generation", "Briefing", "Writing", "Editing", "SEO optimization"]},
            {"heading": "Expected business impact", "subpoints": [self.case_study.result or "More qualified traffic and demo requests"]},
            {"heading": "What we will improve next", "subpoints": ["Add competitor research", "Add publishing integrations"]},
        ]
        return {"target_keyword": keyword, "search_intent": "commercial/informational", "title_options": [title], "selected_title": title, "h1": title, "outline": outline, "faqs": ["How long does one full content run take?", "Can this run without an API key?"], "cta": self.business.main_cta or "Schedule a demo", "internal_link_targets": ["/services/ai-seo-systems"], "meta_title": title[:60], "meta_description": "Case study showing how a proof-based SEO content machine turns project knowledge into publish-ready drafts."}

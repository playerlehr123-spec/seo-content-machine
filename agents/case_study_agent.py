from agents.base import BaseAgent


class CaseStudyAgent(BaseAgent):
    name = "CaseStudyAgent"
    description = "Builds traffic-focused angles"

    def run(self, input_data):
        project = self.case_study.project_name.lower()
        if "local" in project or "signage" in project:
            post_type = "Local SEO Page"
            intent = "location-based/commercial"
        elif "raffle" in project or "fundraising" in project:
            post_type = "Fundraising Ideas Post"
            intent = "informational/commercial"
        else:
            post_type = "Case Study"
            intent = "commercial/informational"
        return {
            "angles": [{
                "title": f"How {self.business.name} Built {self.case_study.project_name}",
                "angle": "Proof-based growth story",
                "target_keyword": self.case_study.project_name.lower(),
                "search_intent": intent,
                "post_type": post_type,
                "business_value": 9,
                "rationale": "Connects real system results to high-intent traffic opportunities."
            }]
        }

from agents.base import BaseAgent


class CaseStudyAgent(BaseAgent):
    name = "CaseStudyAgent"
    description = "Builds case-study angles"

    def run(self, input_data):
        title = f"I Built {self.case_study.project_name} to Create a Repeatable SEO Content Machine"
        return {"angles": [{"title": title, "angle": "Founder/operator case study", "target_keyword": self.case_study.project_name.lower(), "search_intent": "commercial/informational", "business_value": 9, "rationale": "Proof-based project write-up tied to buying intent."}]}

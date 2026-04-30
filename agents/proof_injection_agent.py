from agents.base import BaseAgent


class ProofInjectionAgent(BaseAgent):
    name = "ProofInjectionAgent"
    description = "Suggests proof elements to keep content experience-based"

    def run(self, input_data):
        return {
            "real_assets_needed": {"screenshots": ["Membership renewal reminder screen", "Raffle campaign setup page", "Digital signage sponsor slide example"], "proof_examples": ["Example club type", "Example workflow", "Example CTA", "Example before/after problem"]},
            "proof_points_to_include": [self.case_study.proof_points] if self.case_study and self.case_study.proof_points else ["Before/after workflow outcomes"],
            "screenshots_needed": [self.case_study.screenshots_needed] if self.case_study and self.case_study.screenshots_needed else ["Workflow dashboard screenshot", "CTA placement screenshot"],
            "examples_to_add": [self.case_study.real_examples] if self.case_study and self.case_study.real_examples else ["One real implementation example"],
            "claims_needing_support": ["Any performance uplift claim", "Any compliance claim"],
            "operator_notes_to_add": [self.case_study.lessons_learned] if self.case_study and self.case_study.lessons_learned else ["What we would improve next"]
        }

from agents.base import BaseAgent


class ContentFormatAgent(BaseAgent):
    name = "ContentFormatAgent"
    description = "Chooses format"

    def run(self, input_data):
        return {"recommended_format": "I Built X", "reason": "The project is proof-based and should show what was built.", "alternate_formats": ["Technical Breakdown", "Case Study"]}

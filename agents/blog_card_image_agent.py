from agents.base import BaseAgent


class BlogCardImageAgent(BaseAgent):
    name = "BlogCardImageAgent"
    description = "Creates image prompt"

    def run(self, input_data):
        return {"image_prompt": "Soft futuristic 3D scene, premium SaaS dashboard aesthetic, white and blue-gray palette, abstract connected nodes and automation flows, no text.", "image_alt_text": f"Abstract automation network visual for {self.case_study.project_name}"}

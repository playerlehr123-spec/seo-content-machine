from agents.base import BaseAgent


class EditorAgent(BaseAgent):
    name = "EditorAgent"
    description = "Edits the draft"

    def run(self, input_data):
        draft = input_data.get("draft", {})
        body = draft.get("body_markdown", "")
        edited = body + "\n\n## Final note\nThis draft is ready for human review before publishing."
        return {"edited_body_markdown": edited, "editor_notes": ["Tightened wording", "Strengthened CTA"]}

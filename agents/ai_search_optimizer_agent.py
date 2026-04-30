from agents.base import BaseAgent


class AISearchOptimizerAgent(BaseAgent):
    name = "AISearchOptimizerAgent"
    description = "Optimizes content for AI search answer engines"

    def run(self, input_data):
        keyword = input_data.get("target_keyword", "this query")
        return {
            "ai_answer_block": f"Quick answer: {keyword} works best when the post maps one clear problem to one clear next step and CTA.",
            "definitions_to_include": ["money page", "search intent", "buyer stage"],
            "step_by_step_needed": True,
            "comparison_table_needed": input_data.get("search_intent") == "comparison",
            "faq_improvements": ["Add concise answers (2-4 sentences)", "Add conversion-oriented FAQ question"],
            "entity_terms": ["Google Search", "AI search", "VFW", "American Legion"],
            "proof_or_source_suggestions": ["Reference internal project outputs", "Label assumptions clearly"],
            "ai_search_notes": ["Direct answer block included", "Entity-rich phrasing recommended"]
        }

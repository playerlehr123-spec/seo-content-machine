from agents.base import BaseAgent


class SearchIntentAgent(BaseAgent):
    name = "SearchIntentAgent"
    description = "Classifies search intent and buyer stage"

    def run(self, input_data):
        query = (input_data.get("query") or "").lower()
        if "vs" in query or "compare" in query:
            return {"search_intent": "comparison", "buyer_stage": "solution_aware", "recommended_post_type": "Comparison Post", "reason": "Searcher compares options.", "must_answer_questions": ["What are top options?", "Which option fits this audience?"]}
        if "near" in query or "local" in query or "vfw" in query or "legion" in query:
            return {"search_intent": "local", "buyer_stage": "product_aware", "recommended_post_type": "Local SEO Page", "reason": "Audience/location specific phrase.", "must_answer_questions": ["Is this built for my organization type?", "How quickly can we start?"]}
        if "how to" in query:
            return {"search_intent": "informational", "buyer_stage": "problem_aware", "recommended_post_type": "How-To Guide", "reason": "Instructional query.", "must_answer_questions": ["What steps should I follow?", "Common mistakes?"]}
        return {"search_intent": "commercial", "buyer_stage": "ready_to_buy", "recommended_post_type": "Software Use Case", "reason": "High-intent solution query.", "must_answer_questions": ["How does this solve the problem?", "What page should I visit next?"]}

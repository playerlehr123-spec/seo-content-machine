from agents.base import BaseAgent


class ContentFormatAgent(BaseAgent):
    name = "ContentFormatAgent"
    description = "Chooses best post type by intent"

    def run(self, input_data):
        angle = (input_data.get("angles") or [{}])[0]
        search_intent = angle.get("search_intent", "informational")
        if "location" in search_intent:
            fmt = "Local SEO Page"
        elif "commercial" in search_intent:
            fmt = "Comparison Post"
        elif "informational" in search_intent:
            fmt = "How-To Guide"
        else:
            fmt = angle.get("post_type", "Case Study")
        return {
            "recommended_format": fmt,
            "reason": "Mapped format to search intent and conversion potential.",
            "alternate_formats": ["Case Study", "Software Use Case", "FAQ Post"]
        }

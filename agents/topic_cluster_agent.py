import json
from agents.base import BaseAgent


class TopicClusterAgent(BaseAgent):
    name = "TopicClusterAgent"
    description = "Builds topic clusters around money pages"

    def run(self, input_data):
        money_page = input_data.get("money_page") or "/schedule-demo"
        keywords = json.loads(self.business.primary_keywords_json or "[]")
        posts = []
        for idx, q in enumerate(keywords[:7]):
            posts.append({
                "query": q,
                "title": f"{q.title()}: Practical Guide",
                "post_type": "Software Use Case",
                "intent": "commercial" if "how to" not in q else "informational",
                "priority": "high" if idx < 3 else "medium",
                "internal_link_anchor": q,
            })
        return {
            "money_page": money_page,
            "cluster_name": f"{self.business.name} {money_page} cluster",
            "pillar_topic": money_page.strip("/").replace("-", " "),
            "supporting_posts": posts,
        }

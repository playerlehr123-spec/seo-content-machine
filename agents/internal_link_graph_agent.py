import json
from agents.base import BaseAgent


class InternalLinkGraphAgent(BaseAgent):
    name = "InternalLinkGraphAgent"
    description = "Creates money-page and cluster-aware internal link graph"

    def run(self, input_data):
        pages = json.loads(self.business.money_pages_json or "[]")
        money_page = input_data.get("money_page") or (pages[0] if pages else "/schedule-demo")
        links = [{"source": "new_blog_post", "target": "/schedule-demo", "anchor_text": "schedule a demo", "reason": "Primary conversion action for demo-ready readers."}]
        if money_page != "/schedule-demo":
            links.append({"source": "new_blog_post", "target": money_page, "anchor_text": input_data.get("keyword", "core solution"), "reason": "Relevant money page connected to the topic."})
        return {"money_page": money_page, "supporting_cluster": input_data.get("cluster_name", "core cluster"), "links": links, "cluster_gaps": []}

import json
from agents.base import BaseAgent


class InternalLinkAgent(BaseAgent):
    name = "InternalLinkAgent"
    description = "Builds internal link strategy"

    def run(self, input_data):
        pages = json.loads(self.business.money_pages_json or "[]")
        keywords = json.loads(self.business.primary_keywords_json or "[]")
        links = []
        for idx, page in enumerate(pages[:3]):
            anchor = "schedule a demo" if idx == 0 else (keywords[idx - 1] if idx - 1 < len(keywords) else "learn more")
            links.append({"source": "new_blog_post", "target": page, "anchor_text": anchor, "reason": "Align internal link with conversion path and relevant keyword."})
        return {"links": links}

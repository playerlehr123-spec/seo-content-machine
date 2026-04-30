import base64
from datetime import datetime
import requests
from agents.base import BaseAgent


class WordPressDraftAgent(BaseAgent):
    name = "WordPressDraftAgent"
    description = "Sends reviewed post to WordPress as draft"

    def run(self, input_data):
        post = self.blog_post
        cfg = input_data.get("wp_config", {})
        base = (cfg.get("base_url") or "").rstrip("/")
        username = cfg.get("username") or ""
        app_password = cfg.get("app_password") or ""
        if not (base and username and app_password):
            return {"success": False, "error": "Missing WordPress credentials. Add WORDPRESS_BASE_URL, WORDPRESS_USERNAME, WORDPRESS_APP_PASSWORD."}

        content = post.edited_body_markdown or post.body_markdown or ""
        payload = {"title": post.title or post.seo_title or "Untitled Draft", "slug": post.slug, "excerpt": post.excerpt or "", "content": content, "status": "draft"}
        token = base64.b64encode(f"{username}:{app_password}".encode()).decode()
        headers = {"Authorization": f"Basic {token}"}
        try:
            resp = requests.post(f"{base}/wp-json/wp/v2/posts", json=payload, headers=headers, timeout=20)
            if resp.status_code not in (200, 201):
                return {"success": False, "error": f"WordPress API error {resp.status_code}: {resp.text[:300]}"}
            data = resp.json()
            return {
                "success": True,
                "wordpress_post_id": data.get("id"),
                "wordpress_post_url": data.get("link"),
                "wordpress_edit_url": f"{base}/wp-admin/post.php?post={data.get('id')}&action=edit",
                "wordpress_status": data.get("status", "draft"),
                "sent_to_wordpress_at": datetime.utcnow().isoformat(),
            }
        except Exception as exc:
            return {"success": False, "error": f"WordPress request failed: {exc}"}

from agents.base import BaseAgent


class TrackingPlanAgent(BaseAgent):
    name = "TrackingPlanAgent"
    description = "Creates tracking plan placeholder"

    def run(self, input_data):
        slug = input_data.get("slug", "post")
        return {
            "primary_metric": "demo_clicks",
            "secondary_metrics": ["organic_clicks", "form_submissions", "money_page_clicks"],
            "suggested_utm_campaign": f"seo_{slug}",
            "events_to_track": ["cta_click", "lead_magnet_download", "demo_button_click", "money_page_click"],
            "future_search_console_checks": ["impressions", "clicks", "CTR", "average position", "queries driving impressions"],
        }

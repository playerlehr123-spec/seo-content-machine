import json
from typing import Any
from flask import current_app


class LLMClient:
    def __init__(self):
        self.provider = current_app.config.get("LLM_PROVIDER", "openai")
        self.api_key = current_app.config.get("OPENAI_API_KEY", "")
        self.model = current_app.config.get("LLM_MODEL", "gpt-4o-mini")

    @property
    def mock_mode(self):
        return not bool(self.api_key)

    def generate_json(self, prompt: str, schema_hint: Any = None):
        if self.mock_mode:
            return {"mock": True, "prompt_excerpt": prompt[:120], "schema_hint": schema_hint}
        try:
            from openai import OpenAI
            client = OpenAI(api_key=self.api_key)
            resp = client.responses.create(
                model=self.model,
                input=prompt,
                temperature=0.3,
            )
            text = resp.output_text
            return json.loads(text)
        except Exception:
            return {"mock": True, "note": "Fallback to mock due to API error", "prompt_excerpt": prompt[:120]}

    def generate_text(self, prompt: str):
        if self.mock_mode:
            return f"[MOCK OUTPUT]\n{prompt[:300]}"
        try:
            from openai import OpenAI
            client = OpenAI(api_key=self.api_key)
            resp = client.responses.create(model=self.model, input=prompt, temperature=0.5)
            return resp.output_text
        except Exception:
            return f"[MOCK FALLBACK]\n{prompt[:300]}"

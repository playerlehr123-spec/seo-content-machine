import os
from dotenv import load_dotenv

load_dotenv()


class Config:
    SECRET_KEY = os.getenv("SECRET_KEY", "dev-secret-key")
    SQLALCHEMY_DATABASE_URI = "sqlite:///seo_content_machine.db"
    SQLALCHEMY_TRACK_MODIFICATIONS = False
    LLM_PROVIDER = os.getenv("LLM_PROVIDER", "openai")
    OPENAI_API_KEY = os.getenv("OPENAI_API_KEY", "")
    LLM_MODEL = os.getenv("LLM_MODEL", "gpt-4o-mini")
    WORDPRESS_BASE_URL = os.getenv("WORDPRESS_BASE_URL", "")
    WORDPRESS_USERNAME = os.getenv("WORDPRESS_USERNAME", "")
    WORDPRESS_APP_PASSWORD = os.getenv("WORDPRESS_APP_PASSWORD", "")

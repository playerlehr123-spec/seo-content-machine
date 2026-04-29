# SEO Content Machine

## 1) What this app does
SEO Content Machine is a proof-based, human-reviewed MVP that turns real business case studies into SEO assets using a modular agent pipeline.

## 2) Setup instructions
1. Create a virtual environment.
2. Install dependencies.
3. Copy `.env.example` to `.env`.

## 3) Install dependencies
```bash
pip install -r requirements.txt
```

## 4) Run the app
```bash
python app.py
```

## 5) Seed demo data
Demo data is auto-seeded on first run when the database is empty.

## 6) Mock mode
If `OPENAI_API_KEY` is blank, the app runs in mock mode and still produces structured outputs.

## 7) Add OpenAI API key later
Set `OPENAI_API_KEY` in `.env` and restart the app.

## 8) What is built
- Flask + SQLite + SQLAlchemy app
- Business profiles, case studies, drafts, agent runs pages
- Full content pipeline with modular agents
- Saved briefs, drafts, SEO package, and run logs

## 9) What is not built yet
- Login and user accounts
- Billing
- WordPress publishing
- Google Search Console integration
- Auto publishing

## 10) Suggested next steps
- Add publish workflow with manual approval
- Add richer formatting and markdown rendering
- Add robust OpenAI JSON schema validation

## Future roadmap
- WordPress draft publishing
- Google Search Console integration
- Competitor research agent
- Website crawler
- Refresh old content agent
- Internal link crawler
- Featured image generation
- Social post generator
- Newsletter generator
- Local SEO landing page generator

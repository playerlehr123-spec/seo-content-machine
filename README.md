# SEO Content Machine

SEO Content Machine is a **human-reviewed SEO lead-gen workflow**. It is not an AI spam blog tool.

## What it does
Creates niche long-tail traffic assets and lead assets using an agent pipeline:

Niche opportunity -> intent -> brief -> draft -> edit -> SEO -> AI answer block -> internal links -> money page alignment -> CTA/lead magnet -> image brief -> checklist -> repurposing -> refresh plan -> human review.

## Install
```bash
pip install -r requirements.txt
```

## Run locally
```bash
python app.py
```
- DB auto-initializes.
- Missing `.env` does not crash app.
- Missing `OPENAI_API_KEY` runs in mock mode.

## Environment variables
Set in `.env` or Replit Secrets:
- `OPENAI_API_KEY`
- `LLM_PROVIDER` (default `openai`)
- `LLM_MODEL` (default `gpt-4o-mini`)
- `SECRET_KEY`

## Mock mode
Leave `OPENAI_API_KEY` empty and run pipeline normally.

## Seed demo data
- Click **Seed Demo Data** on dashboard (idempotent).
- Or start app; seed routine only inserts missing businesses.

## Full pipeline test (first flow)
1. Seed demo data
2. Open Club Raffle Pro niche opportunity: `raffle software for VFW`
3. Run Full Content Pipeline
4. Open generated draft
5. Verify: target keyword, SEO title/meta, money page, primary CTA, lead magnet, image brief, internal links, checklist, edited body, agent logs

## Draft Detail checklist
Review SEO/traffic, AI answer block, lead engine, trust checks, internal links, image quality, publish readiness, tracking plan, refresh plan, and edited content.

## Not built yet
- WordPress draft publishing
- Google Search Console integration
- website crawler
- external keyword APIs
- login/billing
- auto publishing

## Replit handoff steps
1. Import repo into Replit
2. Run in mock mode
3. Fix any Replit-specific env/path issues
4. Add OpenAI API key in Replit Secrets
5. Generate real draft
6. Add WordPress draft publishing later
7. Add website crawler later
8. Add Search Console later
9. Add refresh logic using real performance data later

## Image policy
MVP creates image briefs/prompts only. Human review required before using any image.

## WordPress draft posting (draft-only)
Create a WordPress Application Password:
1. WordPress Admin -> Users -> Profile
2. Create Application Password
3. Copy once and store securely

Add Replit Secrets:
- `WORDPRESS_BASE_URL` (e.g. `https://example.com`)
- `WORDPRESS_USERNAME`
- `WORDPRESS_APP_PASSWORD`

Then open a draft and click **Send to WordPress Draft**.
If credentials are missing, the UI shows setup guidance and does not crash.
No live publish is performed in this MVP.

## The TV Sign campaign quality guardrails
Primary campaign: **Turn Screens Into Revenue**.

Content rules enforced in draft generation:
- 450-700 word target range (human reviewer enforces final pass)
- Quick Answer required
- practical examples required
- FAQ limited to max 3
- CTA points to `/contact-us`
- no generic AI intros, no fake stats, no unsupported pricing claims
- no Social Club Pro / Club Raffle Pro context leakage in TV Sign drafts
- use existing image assets only (no AI image generation)
- WordPress posting remains draft-only

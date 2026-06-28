from agents.base import BaseAgent


class ArticleStyleGuardAgent(BaseAgent):
    name = "ArticleStyleGuardAgent"
    description = "Checks article style/structure guardrails for publishable drafts"

    def run(self, input_data):
        text = input_data.get("text") or ""
        business_name = (input_data.get("business_name") or "").lower()
        lowered = text.lower()
        word_count = len(text.split())

        banned_phrases = [
            "in today's digital landscape",
            "this post delivers exactly that",
            "final thoughts",
            "practical takeaway",
            "solution_aware",
            "buyer stage",
        ]
        banned_found = [phrase for phrase in banned_phrases if phrase in lowered]

        wrong_terms = []
        if business_name == "the tv sign":
            for term in ["social club pro", "club raffle pro"]:
                if term in lowered:
                    wrong_terms.append(term)

        pricing_risks = [
            phrase
            for phrase in [
                "guaranteed revenue",
                "pricing starts at",
                "hard roi guarantee",
                "statistically proven",
            ]
            if phrase in lowered
        ]

        required_sections = [
            "quick answer",
            "why it matters",
            "practical examples",
            "how the tv sign helps",
            "common mistakes",
            "faq",
            "cta",
        ]
        missing_items = [
            f"missing section: {section}"
            for section in required_sections
            if f"## {section}" not in lowered and f"# {section}" not in lowered
        ]

        section_count = lowered.count("\n## ") + lowered.count("\n# ")
        if section_count > 7:
            missing_items.append("too many sections (max 7)")

        faq_count = lowered.count("?\n") + lowered.count("?\r\n")
        if faq_count > 3:
            missing_items.append("faq over 3 questions")
        if "/contact-us" not in lowered and business_name == "the tv sign":
            missing_items.append("cta link must be /contact-us")
        if "image" not in lowered:
            missing_items.append("no image recommendation mention")

        passes_length = 450 <= word_count <= 700
        structure_issues = [
            item
            for item in missing_items
            if item.startswith("missing section:") or item == "too many sections (max 7)"
        ]
        passes_structure = not structure_issues
        approved = (
            passes_length
            and passes_structure
            and not banned_found
            and not wrong_terms
            and not pricing_risks
        )

        return {
            "word_count": word_count,
            "passes_length_check": passes_length,
            "passes_structure_check": passes_structure,
            "banned_phrases_found": banned_found,
            "wrong_business_terms_found": wrong_terms,
            "pricing_or_claim_risks": pricing_risks,
            "missing_items": missing_items,
            "style_notes": ["Use short paragraphs and keep one clear CTA block."],
            "approved_for_wordpress_draft": approved,
        }

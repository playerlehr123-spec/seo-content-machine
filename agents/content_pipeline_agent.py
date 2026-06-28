import json
from models import db, ContentBrief, BlogPost
from agents.case_study_agent import CaseStudyAgent
from agents.content_format_agent import ContentFormatAgent
from agents.content_brief_agent import ContentBriefAgent
from agents.blog_writer_agent import BlogWriterAgent
from agents.editor_agent import EditorAgent
from agents.seo_optimizer_agent import SEOOptimizerAgent
from agents.blog_card_image_agent import BlogCardImageAgent
from agents.internal_link_agent import InternalLinkAgent
from agents.article_style_guard_agent import ArticleStyleGuardAgent


class ContentPipelineAgent:
    def __init__(self, business, case_study):
        self.business = business
        self.case_study = case_study

    def run(self):
        case_out = CaseStudyAgent(self.business, self.case_study).execute({})
        format_out = ContentFormatAgent(self.business, self.case_study).execute(case_out)
        angle = (case_out.get("angles") or [{}])[0]
        brief_out = ContentBriefAgent(self.business, self.case_study).execute({"angle": angle, "format": format_out})

        brief = ContentBrief(
            business_id=self.business.id,
            case_study_id=self.case_study.id,
            target_keyword=brief_out.get("target_keyword"),
            search_intent=brief_out.get("search_intent"),
            title_options_json=json.dumps(brief_out.get("title_options", [])),
            selected_title=brief_out.get("selected_title"),
            h1=brief_out.get("h1"),
            outline_json=json.dumps(brief_out.get("outline", [])),
            faqs_json=json.dumps(brief_out.get("faqs", [])),
            cta=brief_out.get("cta"),
            internal_link_targets_json=json.dumps(brief_out.get("internal_link_targets", [])),
            meta_title=brief_out.get("meta_title"),
            meta_description=brief_out.get("meta_description"),
        )
        db.session.add(brief)
        db.session.commit()

        draft_out = BlogWriterAgent(self.business, self.case_study).execute({"brief": brief_out})
        post = BlogPost(
            business_id=self.business.id,
            case_study_id=self.case_study.id,
            content_brief_id=brief.id,
            title=draft_out.get("title"),
            slug=draft_out.get("slug"),
            body_markdown=draft_out.get("body_markdown"),
            status="draft",
        )
        db.session.add(post)
        db.session.commit()

        edit_out = EditorAgent(self.business, self.case_study, post).execute({"draft": draft_out})
        seo_out = SEOOptimizerAgent(self.business, self.case_study, post).execute({"title": post.title})
        img_out = BlogCardImageAgent(self.business, self.case_study, post).execute({})
        link_out = InternalLinkAgent(self.business, self.case_study, post).execute({})
        edited_body = edit_out.get("edited_body_markdown") or draft_out.get("body_markdown", "")
        style_guard_out = ArticleStyleGuardAgent(
            self.business,
            self.case_study,
            post,
        ).execute({"text": edited_body, "business_name": self.business.name})

        post.edited_body_markdown = edit_out.get("edited_body_markdown")
        post.seo_title = seo_out.get("seo_title")
        post.meta_description = seo_out.get("meta_description")
        post.slug = seo_out.get("slug", post.slug)
        post.excerpt = seo_out.get("excerpt")
        post.category = seo_out.get("category")
        post.tags_json = json.dumps(seo_out.get("tags", []))
        post.image_prompt = img_out.get("image_prompt")
        post.image_alt_text = img_out.get("image_alt_text")
        post.internal_links_json = json.dumps(link_out.get("links", []))
        post.publish_readiness_json = json.dumps({"article_style_guard": style_guard_out})
        db.session.commit()
        return post

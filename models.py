from datetime import datetime
from flask_sqlalchemy import SQLAlchemy


db = SQLAlchemy()


class BusinessProfile(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(255), nullable=False)
    website_url = db.Column(db.String(255))
    audience = db.Column(db.Text)
    offer = db.Column(db.Text)
    brand_voice = db.Column(db.Text)
    main_cta = db.Column(db.String(255))
    core_topics_json = db.Column(db.Text)
    created_at = db.Column(db.DateTime, default=datetime.utcnow)


class ProjectCaseStudy(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    business_id = db.Column(db.Integer, db.ForeignKey('business_profile.id'), nullable=False)
    project_name = db.Column(db.String(255), nullable=False)
    problem_solved = db.Column(db.Text)
    system_built = db.Column(db.Text)
    tools_used = db.Column(db.Text)
    before_state = db.Column(db.Text)
    after_state = db.Column(db.Text)
    result = db.Column(db.Text)
    target_reader = db.Column(db.String(255))
    notes = db.Column(db.Text)
    created_at = db.Column(db.DateTime, default=datetime.utcnow)


class ContentBrief(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    business_id = db.Column(db.Integer, db.ForeignKey('business_profile.id'), nullable=False)
    case_study_id = db.Column(db.Integer, db.ForeignKey('project_case_study.id'), nullable=False)
    target_keyword = db.Column(db.String(255))
    search_intent = db.Column(db.String(255))
    title_options_json = db.Column(db.Text)
    selected_title = db.Column(db.String(255))
    h1 = db.Column(db.String(255))
    outline_json = db.Column(db.Text)
    faqs_json = db.Column(db.Text)
    cta = db.Column(db.String(255))
    internal_link_targets_json = db.Column(db.Text)
    meta_title = db.Column(db.String(255))
    meta_description = db.Column(db.Text)
    created_at = db.Column(db.DateTime, default=datetime.utcnow)


class BlogPost(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    business_id = db.Column(db.Integer, db.ForeignKey('business_profile.id'), nullable=False)
    case_study_id = db.Column(db.Integer, db.ForeignKey('project_case_study.id'), nullable=False)
    content_brief_id = db.Column(db.Integer, db.ForeignKey('content_brief.id'))
    title = db.Column(db.String(255))
    slug = db.Column(db.String(255))
    excerpt = db.Column(db.Text)
    category = db.Column(db.String(255))
    tags_json = db.Column(db.Text)
    body_markdown = db.Column(db.Text)
    edited_body_markdown = db.Column(db.Text)
    seo_title = db.Column(db.String(255))
    meta_description = db.Column(db.Text)
    image_prompt = db.Column(db.Text)
    image_alt_text = db.Column(db.String(255))
    internal_links_json = db.Column(db.Text)
    status = db.Column(db.String(50), default='draft')
    created_at = db.Column(db.DateTime, default=datetime.utcnow)
    updated_at = db.Column(db.DateTime, default=datetime.utcnow, onupdate=datetime.utcnow)


class AgentRun(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    business_id = db.Column(db.Integer, db.ForeignKey('business_profile.id'), nullable=False)
    case_study_id = db.Column(db.Integer, db.ForeignKey('project_case_study.id'), nullable=False)
    blog_post_id = db.Column(db.Integer, db.ForeignKey('blog_post.id'))
    agent_name = db.Column(db.String(100), nullable=False)
    input_json = db.Column(db.Text)
    output_json = db.Column(db.Text)
    status = db.Column(db.String(50), default='started')
    error_message = db.Column(db.Text)
    started_at = db.Column(db.DateTime, default=datetime.utcnow)
    finished_at = db.Column(db.DateTime)

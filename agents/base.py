import json
from datetime import datetime
from models import db, AgentRun


class BaseAgent:
    name = "BaseAgent"
    description = "Base agent"

    def __init__(self, business, case_study=None, blog_post=None):
        self.business = business
        self.case_study = case_study
        self.blog_post = blog_post

    def execute(self, input_data):
        run = AgentRun(
            business_id=self.business.id,
            case_study_id=self.case_study.id if self.case_study else None,
            blog_post_id=self.blog_post.id if self.blog_post else None,
            agent_name=self.name,
            input_json=json.dumps(input_data),
            status="started",
            started_at=datetime.utcnow(),
        )
        db.session.add(run)
        db.session.commit()
        try:
            output = self.run(input_data)
            run.output_json = json.dumps(output)
            run.status = "success"
            run.finished_at = datetime.utcnow()
            db.session.commit()
            return output
        except Exception as exc:
            run.status = "failed"
            run.error_message = str(exc)
            run.finished_at = datetime.utcnow()
            db.session.commit()
            return {"error": str(exc), "agent": self.name}

    def run(self, input_data):
        raise NotImplementedError

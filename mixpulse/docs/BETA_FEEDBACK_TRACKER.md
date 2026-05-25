# WaveFrame Beta Feedback Tracker

This is a lightweight manual tracker for private beta feedback. GitHub issues can replace rows once a report is confirmed.

Status values:
- New
- Needs info
- Confirmed
- In progress
- Fixed
- Needs retest
- Deferred
- Closed

Decision values:
- Fix now
- Fix before beta
- Defer
- Roadmap
- Won't fix
- Duplicate

| ID | Date | Tester | Build / Artifact | Area | Severity | Summary | Repro steps | Repro rate | Environment | Status | Owner | Decision | Linked Issue / PR | Notes |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| EX-001 | YYYY-MM-DD | Example | Run # | Output window | P1 | Example placeholder: output close/reopen crash | Open Output, close, reopen | Always | Windows / Standalone | Needs info | Unassigned | Fix before beta | TBD | Placeholder row only |
| EX-002 | YYYY-MM-DD | Example | Run # | Feature request | Feature | Example placeholder: built-in video export | N/A | N/A | Any | Deferred | Unassigned | Roadmap | TBD | Placeholder row only; video export is future/TODO |

## Tracker Rules

- Keep one row per issue or feedback theme.
- Move confirmed bugs to GitHub issues when they need code work.
- Keep P0/P1 rows at the top during fix sprint planning.
- Mark feature requests as Roadmap unless they block the v0.1 beta promise.
- After a fix lands, set status to Needs retest until a tester verifies it.

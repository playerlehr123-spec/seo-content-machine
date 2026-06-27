# WaveFrame v0.2 Backlog

Use this backlog to plan v0.2 without mixing private beta blockers, polish, and feature ideas together.

Status values:
- New
- Needs info
- Ready
- In progress
- Fixed
- Needs retest
- Deferred
- Closed

| ID | Area | Type | Priority | Summary | Source | Status | Target Sprint | Notes |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| EX-001 | QA | Bug | P1 | Example placeholder: output close/reopen issue from beta feedback | Beta feedback | Needs info | Sprint 1 | Placeholder row only |
| EX-002 | Visual Modules | Polish | P2 | Example placeholder: Logo Reactor needs stronger visual hierarchy | Internal review | New | Sprint 2 | Placeholder row only |
| EX-003 | Templates | Feature | P3 | Example placeholder: deeper template field editing | Parking lot | Deferred | Sprint 3 | Placeholder row only |
| EX-004 | Naming | Research | P2 | Example placeholder: WaveFrame naming cleanup stage 1 plan | Naming plan | New | Sprint 6 | Placeholder row only |
| WF-S1-001 | Templates | Bug | P1 | Add safe fallback for invalid module/template selection state | Defensive QA | Needs retest | Sprint 1 | Fixed in Sprint 1; verify rapid switching and default/malformed states |
| WF-S1-002 | Presets | Bug | P1 | Clamp malformed brand preset logo values | Defensive QA | Needs retest | Sprint 1 | Fixed in Sprint 1; verify malformed preset load does not crash or over-scale |
| WF-S1-003 | Output | Bug | P2 | Add safe fallback for missing/invalid export preset selection | Defensive QA | Needs retest | Sprint 1 | Fixed in Sprint 1; verify export preset and template switching |
| WF-S3-001 | Templates | Polish | P2 | Expand starter template metadata and status labels | v0.2 Sprint 3 | Needs retest | Sprint 3 | Implemented in Sprint 3; verify all 10 templates display purpose/module/status |
| WF-S3-002 | Brand Kit | Polish | P2 | Improve brand defaults and preview fallback text | v0.2 Sprint 3 | Needs retest | Sprint 3 | Implemented in Sprint 3; verify reset restores readable defaults |
| WF-S3-003 | Templates | Polish | P2 | Show template/module/brand state in preview canvas | v0.2 Sprint 3 | Needs retest | Sprint 3 | Implemented in Sprint 3; verify overlay remains readable at common window sizes |
| WF-S4-001 | Presets | Polish | P2 | Add built-in creator session preset selector | v0.2 Sprint 4 | Needs retest | Sprint 4 | Implemented in Sprint 4; verify all 8 presets update template/module/export/color state |
| WF-S4-002 | Presets | Bug | P2 | Normalize Brand preset save/load values and keep current session on load failure | v0.2 Sprint 4 | Needs retest | Sprint 4 | Implemented in Sprint 4; verify missing/malformed JSON fails safely |
| WF-S4-003 | Presets | Polish | P2 | Clarify reset/default and Brand preset status messages | v0.2 Sprint 4 | Needs retest | Sprint 4 | Implemented in Sprint 4; verify reset restores default session and truthful status |
| WF-S5-001 | Output | Bug | P2 | Harden output close/reopen/fullscreen state | v0.2 Sprint 5 | Needs retest | Sprint 5 | Implemented in Sprint 5; verify repeated Output clicks, close/reopen, and fullscreen do not crash |
| WF-S5-002 | OBS | Polish | P2 | Add clearer OBS Capture Mode and still-PNG-only messaging | v0.2 Sprint 5 | Needs retest | Sprint 5 | Implemented in Sprint 5; verify output overlay is readable in OBS Window Capture |
| WF-S5-003 | Export | Polish | P2 | Clarify aspect/safe-area guides and Frame status text | v0.2 Sprint 5 | Needs retest | Sprint 5 | Implemented in Sprint 5; verify 9:16, 1:1, 4:5, and 16:9 guide/status behavior |
| WF-S7-001 | Brand Kit | Feature | P2 | Add editable Artist, Track, Label, and CTA fields | v0.2 Sprint 7 | Needs retest | Sprint 7 | Verify edits update preview/output text and empty fields fallback safely |
| WF-S7-002 | Templates | Polish | P2 | Add template-aware Brand Text helper labels | v0.2 Sprint 7 | Needs retest | Sprint 7 | Verify template switching keeps fields visible and coherent |
| WF-S7-003 | Presets | Polish | P2 | Sync editable Brand Text with reset, session presets, and Brand preset save/load | v0.2 Sprint 7 | Needs retest | Sprint 7 | Verify reset/session/load update text fields without losing safe defaults |
| WF-S6-001 | Export | Polish | P2 | Clarify export preset labels, dimensions, use cases, and still-PNG workflow | v0.2 Sprint 6 | Needs retest | Sprint 6 | Implemented in Sprint 6; verify each preset displays correct aspect/dimensions/use case |
| WF-S6-002 | Export | Bug | P2 | Harden Frame/current-frame PNG failure messaging | v0.2 Sprint 6 | Needs retest | Sprint 6 | Implemented in Sprint 6; verify Frame before Output, repeated Frame clicks, and future-only presets fail safely |
| WF-S6-003 | Docs | Docs | P2 | Align export, OBS, QA, and beta docs around still-frame vs future video export | v0.2 Sprint 6 | Needs retest | Sprint 6 | Verify docs do not imply MP4/WebM/timeline export exists |

## Areas

- Visual Modules
- Templates
- Brand Kit
- Presets
- Output
- OBS
- DAW
- QA
- Docs
- Naming
- Packaging

## Types

- Bug
- Polish
- Feature
- Research
- Docs

## Priorities

- P0
- P1
- P2
- P3

## Backlog Rules

- P0/P1 bugs come from beta feedback and go first.
- Feature ideas belong here or in `V0_2_PARKING_LOT.md` until selected.
- Do not use this backlog to justify forbidden scope.
- Keep one backlog item per issue or feature candidate.




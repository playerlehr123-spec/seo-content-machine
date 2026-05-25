# WaveFrame GitHub Labels

These labels are recommended for private beta triage. This document does not require automatic label creation.

| Label | Meaning | Use when |
| --- | --- | --- |
| `beta` | Private beta feedback | Any tester report from a beta artifact |
| `bug` | Defect | Something expected does not work |
| `feature` | Feature idea | New behavior or workflow request |
| `docs` | Documentation | Guide, install, release, or wording issue |
| `qa` | Testing/process | Test matrix, smoke test, or verification item |
| `p0-blocker` | Blocks beta | Launch, build, scan/load, audio pass-through, crash on open |
| `p1-major` | Major workflow bug | Output, module switching, Frame/HUD, preset, or DAW remove/reload crash |
| `p2-minor` | Non-blocking bug | Layout, text, visual glitch, docs mismatch |
| `p3-polish` | Polish | Spacing, copy, color, visual taste |
| `daw` | DAW issue | Plugin scan/load/remove/reload issue |
| `obs` | OBS workflow | OBS capture or capture instructions |
| `output-window` | Output window | Separate capture/output window behavior |
| `audio-pass-through` | Audio safety | Any report that audio is changed, muted, distorted, or routed incorrectly |
| `visual-module` | Visual module | Spectrum, Logo Reactor, Type Pulse, Promo Card, Particles |
| `template-system` | Template workflow | Template selection, mapping, or social layout |
| `preset-system` | Preset/state | Save, load, reset, state recall |
| `needs-info` | Missing details | Cannot triage until tester adds details |
| `needs-retest` | Fix needs verification | Code/docs changed and tester should retry |
| `deferred` | Not in current sprint | Valid but not for immediate fix |
| `roadmap` | Future work | Feature idea or larger deferred direction |

## Recommended Label Combos

- Audio pass-through report: `beta`, `bug`, `p0-blocker`, `audio-pass-through`.
- DAW scan/load issue: `beta`, `bug`, `p0-blocker`, `daw`.
- Output crash: `beta`, `bug`, `p1-major`, `output-window`.
- OBS capture confusion: `beta`, `docs` or `bug`, `p2-minor`, `obs`.
- Visual taste feedback: `beta`, `p3-polish`, `visual-module`.
- New module idea: `beta`, `feature`, `roadmap`, `visual-module`.

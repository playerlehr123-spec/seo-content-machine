# WaveFrame DAW Test Matrix

Use this table during private beta to track VST3 compatibility. Status values: Untested, Pass, Fail, Needs retest.

| DAW | Version | Plugin scanned | Plugin loads | Audio pass-through unchanged | Meters move | UI opens | Output opens | Frame works | HUD works | Remove/reload works | Notes |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Ableton Live |  | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested |  |
| FL Studio |  | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested |  |
| Reaper |  | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested |  |
| Bitwig |  | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested |  |
| Other |  | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested |  |

## Notes
- Test VST3 scanning separately from plugin loading.
- Confirm audio pass-through with a known source before judging visual behavior.
- Record DAW crashes with exact plugin actions: scan, load, UI open, Output, Frame, HUD, remove, reload, save, or reopen project.
- Do not mark a DAW as Pass until remove/reload has been tested.

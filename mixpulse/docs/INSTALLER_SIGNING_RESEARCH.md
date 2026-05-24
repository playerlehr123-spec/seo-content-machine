# WaveFrame Installer and Signing Research

This is research only. Do not implement an installer, signing scripts, certificates, secrets, artifact renames, plugin ID changes, or workflow changes from this document without a dedicated implementation PR.

## Current Recommendation
- Private beta: keep the current ZIP-style GitHub Actions artifact.
- Later beta: evaluate Inno Setup or NSIS for a simple signed installer.
- Public release: use a signed installer, release notes, support docs, and a stable naming strategy.

MixPulse remains the internal CMake target, plugin identity, and artifact name for now. WaveFrame remains the user-facing product name.

## Windows Installer Options

| Option | What it is | Pros | Cons | Difficulty | Private beta? | Public release? | Signing requirements | Workflow risk |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| ZIP-only beta artifact | GitHub Actions artifact containing README, EXE, and/or VST3 | Already works, low risk, transparent contents | Manual install, unsigned warnings, no uninstall | Low | Best current choice | Not ideal alone | Optional but unsigned warnings remain | Low |
| Manual VST3 install package | ZIP focused on `MixPulse.vst3` and instructions | Simple for DAW testers, avoids installer complexity | User must copy bundle and rescan DAW | Low | Good for plugin-only testers | Weak for public release | Optional for ZIP, recommended for public downloads | Low |
| Inno Setup | Scriptable Windows installer | Good balance of simplicity and polish, common for indie desktop apps, supports signing hooks | Custom scripting still needed for VST3 paths/uninstall | Medium | Later beta candidate | Good candidate | Sign installer; optionally sign EXE/VST3 first | Medium |
| NSIS | Scriptable Windows installer/uninstaller system | Flexible, lightweight, common, mature | Script complexity can grow; signing/uninstaller flow needs care | Medium | Later beta candidate | Good candidate | Sign installer and generated uninstaller; optionally sign payloads first | Medium |
| WiX Toolset | XML-based toolset for Windows Installer MSI packages | Enterprise-friendly MSI output, deterministic, powerful | Higher learning curve, more ceremony | High | Probably overkill | Good for mature release | Sign MSI and payloads as needed | Medium/high |
| MSIX | Modern Windows app package format | Clean install/uninstall model, strong package identity | Must be signed; VST3/common-file install flow may not fit plugin distribution well | High | Not recommended now | Research later | MSIX packages must be signed for install outside Store-style flows | High |

## Code Signing Overview

Unsigned Windows downloads commonly trigger warnings because Windows cannot verify the publisher and may not have SmartScreen reputation for the binary. Code signing attaches a publisher identity and integrity signature to an EXE, installer, or package. It does not guarantee the software is bug-free; it helps Windows and users verify who published the file and whether it was modified.

### Certificate Types
- Standard/OV code signing certificate: normal public-trust code signing identity. It may still need reputation over time.
- EV code signing certificate: stronger organization validation, often hardware-token backed, historically associated with better SmartScreen reputation behavior. Current SmartScreen behavior should be verified before purchase.
- Azure Artifact Signing: Microsoft-managed signing service worth researching for Windows distribution.
- Self-signed certificate: useful only for local/internal machines that explicitly trust it; not suitable for public release.

### What To Sign Later
- Standalone EXE.
- Installer EXE or MSI.
- VST3 binaries inside the `.vst3` bundle if applicable.
- MSIX package if that path is ever chosen.

### CI Secret Handling Later
- Do not commit certificates, PFX files, passwords, tokens, or private keys.
- Store signing credentials in a secure CI secret store only after the signing model is chosen.
- Prefer managed signing or hardware-backed signing for public release.
- Add signing as a separate workflow stage after the unsigned CI build remains green.

## VST3 Distribution Notes

Current private beta VST3 install path:

```text
C:\Program Files\Common Files\VST3\
```

Future installers can copy the VST3 bundle there automatically, add a standalone app location, add Start Menu shortcuts, and register an uninstall entry.

Do not rename `MixPulse.vst3`, plugin IDs, bundle IDs, or product metadata until DAW scan/load/remove/reload and saved-project recall behavior is tested.

## Recommended Staged Path

### Stage 0 - Current Internal CI Artifact
- Keep `MixPulse-Windows-Beta`.
- Keep `MixPulse-Windows-Build-Folder`.
- Keep ZIP/manual install.
- Keep unsigned warning documented.

### Stage 1 - Private Beta ZIP
- Keep current artifact names.
- Improve `README_INSTALL.txt` copy.
- Include clear VST3 install instructions.
- Include OBS capture and no-video-export notes.
- Use bug report and release checklist docs.

### Stage 2 - Signed Beta Installer Research
- Prototype Inno Setup or NSIS on a separate branch.
- Keep plugin IDs and artifact names stable during prototype.
- Decide whether installer places standalone EXE, VST3, or both.
- Add uninstall behavior.
- Add signing only after installer contents are stable.

### Stage 3 - Public Beta
- Signed installer.
- Stable version label.
- Release notes.
- Website/download-page copy.
- Known issues and support docs.

### Stage 4 - Public Release
- Final installer/signing policy.
- Final naming cleanup decisions.
- Final plugin identity decision.
- Regression-tested DAW compatibility.

## Decisions Needed Later
- Inno Setup vs NSIS vs WiX.
- Whether to ship standalone-only, VST3-only, or combined installer.
- Whether VST3 installer path is fixed or user-selectable.
- Certificate/provider choice.
- Signing location: local release machine, CI, or managed signing.
- Final WaveFrame plugin ID/name timing.

## Sources Checked
- Microsoft SignTool documentation: https://learn.microsoft.com/en-us/windows/win32/seccrypto/signtool
- Microsoft MSIX signing documentation: https://learn.microsoft.com/en-us/windows/msix/package/sign-msix-package-guide
- Microsoft Azure Artifact Signing documentation: https://learn.microsoft.com/en-us/azure/trusted-signing/
- Inno Setup SignTool documentation: https://documentation.help/inno-setup/topic_setup_signtool.htm
- NSIS documentation: https://nsis.sourceforge.io/Docs/
- WiX Toolset documentation: https://documentation.help/WiX-Toolset/
- Steinberg VST plug-in locations: https://helpcenter.steinberg.de/hc/en-us/articles/115000177084

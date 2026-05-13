# Analyzer Notes

Implemented analyzer values are real-time placeholders for UI modulation, while preserving pass-through audio behavior.

- Real-time: peakL, peakR, rmsL, rmsR, band energies.
- Placeholder: truePeak mirrors samplePeak; lufsM is estimated and not standards-compliant LUFS.
- Meter ticks preserved: 0, -3, -6, -9, -12, -24 dB.
- LUFS reference lines preserved: -6, -12, -14, -23 LUFS.

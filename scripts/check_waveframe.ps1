param(
    [string]$JuceDir = ""
)

$ErrorActionPreference = "Stop"

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$RepoRoot = Split-Path -Parent $ScriptDir
$MixPulseDir = Join-Path $RepoRoot "mixpulse"
$BuildDir = Join-Path $MixPulseDir "build"
$CMakeLists = Join-Path $MixPulseDir "CMakeLists.txt"

function Fail-WaveFrameCheck {
    param(
        [string]$Message
    )

    Write-Host "ERROR: $Message" -ForegroundColor Red
    exit 1
}

if ([string]::IsNullOrWhiteSpace($JuceDir)) {
    if (-not [string]::IsNullOrWhiteSpace($env:JUCE_DIR)) {
        $JuceDir = $env:JUCE_DIR
    }
    else {
        $DefaultJuceDir = Join-Path $RepoRoot "_deps/JUCE"
        if (Test-Path -Path $DefaultJuceDir) {
            $JuceDir = $DefaultJuceDir
        }
        else {
            Fail-WaveFrameCheck "JUCE_DIR is required. Pass -JuceDir C:/path/to/JUCE, set the JUCE_DIR environment variable, or place JUCE at $DefaultJuceDir."
        }
    }
}

if (-not (Test-Path -Path $CMakeLists)) {
    Fail-WaveFrameCheck "Missing CMake project: $CMakeLists"
}

if (-not (Test-Path -Path $JuceDir)) {
    Fail-WaveFrameCheck "JUCE path does not exist: $JuceDir"
}

Write-Host "WaveFrame build doctor"
Write-Host "Repo root: $RepoRoot"
Write-Host "JUCE_DIR: $JuceDir"

Push-Location $RepoRoot
try {
    Write-Host "Configuring MixPulse..."
    & cmake -S mixpulse -B mixpulse/build -DJUCE_DIR="$JuceDir" -DMIXPULSE_BUILD_VST3=ON -DMIXPULSE_BUILD_STANDALONE=ON -DMIXPULSE_BUILD_AU=OFF
    if ($LASTEXITCODE -ne 0) {
        Fail-WaveFrameCheck "CMake configure failed."
    }

    Write-Host "Building MixPulse_Standalone..."
    & cmake --build mixpulse/build --config Release --target MixPulse_Standalone
    $BuildExitCode = $LASTEXITCODE

    if ($BuildExitCode -ne 0) {
        Write-Warning "MixPulse_Standalone target failed. Trying ALL_BUILD..."
        & cmake --build mixpulse/build --config Release --target ALL_BUILD
        $BuildExitCode = $LASTEXITCODE
    }

    if ($BuildExitCode -ne 0) {
        Fail-WaveFrameCheck "CMake build failed."
    }

    Write-Host "Found WaveFrame/MixPulse artifacts:"
    $Artifacts = Get-ChildItem -Path $BuildDir -Recurse -File -Include "*.exe","*.vst3" -ErrorAction SilentlyContinue
    if ($Artifacts) {
        $Artifacts | ForEach-Object { Write-Host $_.FullName }
    }
    else {
        Write-Warning "Build completed, but no EXE or VST3 files were found under $BuildDir."
    }

    Write-Host "WaveFrame build doctor passed"
}
finally {
    Pop-Location
}

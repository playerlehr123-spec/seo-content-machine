cmake_minimum_required(VERSION 3.22)
project(MixPulse VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(MIXPULSE_BUILD_VST3 "Build VST3 format" ON)
option(MIXPULSE_BUILD_STANDALONE "Build Standalone app" ON)
option(MIXPULSE_BUILD_AU "Build AU format (Apple only)" ${APPLE})

set(_formats "")
if(MIXPULSE_BUILD_VST3)
    list(APPEND _formats VST3)
endif()
if(MIXPULSE_BUILD_STANDALONE)
    list(APPEND _formats Standalone)
endif()
if(APPLE AND MIXPULSE_BUILD_AU)
    list(APPEND _formats AU)
endif()
if(UNIX AND NOT APPLE)
    set(_formats Standalone)
endif()

if(NOT DEFINED JUCE_DIR)
    message(STATUS "JUCE_DIR not set. Pass -DJUCE_DIR=/path/to/JUCE or install JUCEConfig.cmake in CMAKE_PREFIX_PATH.")
endif()

if(DEFINED JUCE_DIR AND EXISTS "${JUCE_DIR}/CMakeLists.txt")
    add_subdirectory(${JUCE_DIR} JUCE)
else()
    find_package(JUCE CONFIG REQUIRED)
endif()

juce_add_plugin(MixPulse
    COMPANY_NAME "MixPulse"
    BUNDLE_ID com.mixpulse.plugin
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    VST3_CATEGORIES "Fx|Analyzer"
    AU_MAIN_TYPE kAudioUnitType_Effect
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    COPY_PLUGIN_AFTER_BUILD FALSE
    PLUGIN_MANUFACTURER_CODE MxPl
    PLUGIN_CODE Mpv1
    FORMATS ${_formats}
    PRODUCT_NAME "MixPulse")

juce_generate_juce_header(MixPulse)

target_sources(MixPulse PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
    Source/AudioAnalyzer.cpp
    Source/TapTempoEngine.cpp
    Source/BeatPulseEngine.cpp
    Source/ThemeManager.cpp
    Source/VisualizerState.cpp
    Source/VisualizerRenderer.cpp
    Source/SpectrumBarsRenderer.cpp
    Source/VisualizerWindow.cpp
    Source/VisualRack.cpp)

target_include_directories(MixPulse PRIVATE include)

target_compile_definitions(MixPulse PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(MixPulse PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_plugin_client
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_core
    juce::juce_dsp
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_opengl
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags)

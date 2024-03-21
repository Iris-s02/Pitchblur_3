/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Week3PluginAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    Week3PluginAudioProcessorEditor (Week3PluginAudioProcessor&);
    ~Week3PluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    //Dry/Wet
    juce::Slider mDryWetSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mDryWetSliderAttachment;
    
    juce::Label  DryWetLabel; //Label
    
    //Blur
    juce::Slider mBlurSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mBlurSliderAttachment;
    
    juce::Label  BlurLabel; //Label
    
    //Gate
    juce::Slider mGateSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mGateSliderAttachment;
    
    juce::Label  GateLabel; //Label
    
    //Reduction
    juce::Slider mReductionSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mReductionSliderAttachment;
    
    juce::Label  ReductionLabel; //Label
    
    //Pitch Shift
    juce::Slider mPitchSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mPitchSliderAttachment;
    
    
    juce::Label  PitchLabel; //Label
    
    //FFT size
    juce::Slider mFFTSizeSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mFFTSizeSliderAttachment;
    
    //FFT Dropdown
    //std::unique_ptr<juce::ComboBox> mFFTSizeDropdown;
    juce::ComboBox mFFTSizeDropdown;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> mFFTSizeDropdownAttachment;
    
    juce::Label  FFTSizeLabel; //Label
    
    //HarmVsNoise
    juce::Slider mHarmVsNoiseSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mHarmVsNoiseSliderAttachment;
    
    juce::Label  HarmVsNoiseLabel; //Label
    
    //HarmVsNoise Button
    juce::TextButton HarmVsNoiseButton {"DeNoise"};
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mHarmVsNoiseButtonAttachment;
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Week3PluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week3PluginAudioProcessorEditor)
};

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
//#include "FFTProcessor.h"

//set FFT Sizes
enum FFTSizes {
    OneTwentyEight,
    FiveTwelve,
    TwoFiftySix,
    TenTwentyFour
};

//==============================================================================
/**
*/
class Week3PluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Week3PluginAudioProcessor();
    ~Week3PluginAudioProcessor() override;
    
    
    // AUDIO FUNCTIONS
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    
    // EXPOSE VTS TO EDITOR
    juce::AudioProcessorValueTreeState& getVTS() {
        return *mValueTreeState;
    };
    
    
    // PRESET / STATE FUNCTIONS
    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    
    // ABOUT THE PLUGIN FUNCTIONS
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    
private:
    
    // We need a separate FFTProcessor for each channel.
   // FFTProcessor fft[2];

        
//    float mSineTonePhase = 0.f;
//
    std::atomic<float>* mDryWet = nullptr;
    std::atomic<float>* mBlur = nullptr;
    std::atomic<float>* mGate = nullptr;
    std::atomic<float>* mDenoise = nullptr;
    std::atomic<float>* mDeHarm = nullptr;
    std::atomic<bool>* mHarmVsNoise = nullptr;
    
    
//
//    juce::LinearSmoothedValue<float> mSmoothedDryWet;
//    juce::LinearSmoothedValue<float> mSmoothedFeedback;
//    juce::LinearSmoothedValue<float> mSmoothedTime;

    std::unique_ptr<juce::AudioProcessorValueTreeState> mValueTreeState;
    
    // value tree construction function, this needs to be called in the constructor of the plugin.
    void _constructValueTreeState();
            
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week3PluginAudioProcessor)
};

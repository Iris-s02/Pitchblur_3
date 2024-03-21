/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
///
//==============================================================================
Week3PluginAudioProcessor::Week3PluginAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       )
{
    _constructValueTreeState();
    
    mDryWet = mValueTreeState->getRawParameterValue("dry_wet");
    mBlur = mValueTreeState->getRawParameterValue("blur");
    mGate = mValueTreeState->getRawParameterValue("gate");
   // mHarmVsNoise = mValueTreeState->getRawParameterValue("harmVsNoise");
    //mDenoise = mValueTreeState->getRawParameterValue("gate");
//
//    mSmoothedDryWet.setCurrentAndTargetValue(0.5f);
//    mSmoothedFeedback.setCurrentAndTargetValue(0.5f);
//    mSmoothedTime.setCurrentAndTargetValue(0.5f);
}

//==============================================================================
void Week3PluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
//    mSmoothedDryWet.reset(sampleRate, .01f);
//    mSmoothedFeedback.reset(sampleRate, .01f);
//    mSmoothedTime.reset(sampleRate, .01f);
}

void Week3PluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{   
    // update the smoothed gain value
//    mSmoothedDryWet.setTargetValue(*mDryWet);
//    mSmoothedFeedback.setTargetValue(*mFeedback);
//    mSmoothedTime.setTargetValue(*mTime);
//    
    
    // BUFFER POINTERS
    float* left_channel = buffer.getWritePointer(0);
    float* right_channel = buffer.getWritePointer(1);
    
    // --------------------------
    // Sine Tone Generation Start
    // --------------------------
    /*
    float sine_hz = 80.f;
    float phase_delta = sine_hz / getSampleRate();
    
    for (int sample_idx = 0; sample_idx < buffer.getNumSamples(); sample_idx++) {
        
        float sine_out = std::sin(mSineTonePhase * 2 * M_PI);
                
        mSineTonePhase += phase_delta;
        
        if (mSineTonePhase > 1.f) {
            mSineTonePhase -= 1.f;
        }
        
        left_channel[sample_idx] = sine_out;
        right_channel[sample_idx] = sine_out;
    }
    // ------------------------
    // Sine Tone Generation End
    // ------------------------
    */
    // --------------------
    // Gain Computation End
    // --------------------
}

Week3PluginAudioProcessor::~Week3PluginAudioProcessor()
{
}


//==============================================================================
const juce::String Week3PluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Week3PluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Week3PluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Week3PluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Week3PluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Week3PluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Week3PluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Week3PluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Week3PluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void Week3PluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void Week3PluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Week3PluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

//==============================================================================
bool Week3PluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Week3PluginAudioProcessor::createEditor()
{
    return new Week3PluginAudioProcessorEditor (*this);
}

//==============================================================================
void Week3PluginAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = mValueTreeState->copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary (*xml, destData);
}

void Week3PluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary (data, sizeInBytes));
    mValueTreeState->replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
void Week3PluginAudioProcessor::_constructValueTreeState()
{
    mValueTreeState.reset(new juce::AudioProcessorValueTreeState(*this, nullptr, juce::Identifier ("My_First_Plugin"),
    {
        std::make_unique<juce::AudioParameterFloat> ("dry_wet", // parameterID
                                                     "Dry/Wet", // parameter name
                                                     0.0f,   // minimum value
                                                     1.0f,   // maximum value
                                                     0.5f),   // default value
        
        std::make_unique<juce::AudioParameterFloat> ("blur", // parameterID
                                                     "Spectral Blur", // parameter name
                                                     0.0f,   // minimum value
                                                     1.0f,   // maximum value
                                                     0.5f),   // default value
        
        std::make_unique<juce::AudioParameterFloat> ("gate", // parameterID
                                                     "Spectral Gate", // parameter name
                                                     0.0f,   // minimum value
                                                     1.0f,   // maximum value
                                                     0.5f),  // default value
        
        std::make_unique<juce::AudioParameterFloat> ("pitchshift", // parameterID
                                                     "Pitch Shift", // parameter name
                                                     0.0f,   // minimum value
                                                     1.0f,   // maximum value
                                                     0.5f),   // default value
        
        std::make_unique<juce::AudioParameterFloat> ("reduction", // parameterID
                                                     "Reduction", // parameter name
                                                     0.0f,   // minimum value
                                                     1.0f,   // maximum value
                                                     0.5f),   // default value
        
        std::make_unique<juce::AudioParameterFloat> ("harmVsNoise", // parameterID
                                                     "Harm Vs Noise", // parameter name
                                                     0.0f,   // minimum value
                                                     1.0f,   // maximum value
                                                     0.5f),   // default value
        
//        std::make_unique<juce::AudioParameterFloat> ("FFTSize", // parameterID
//                                                     "FFT Size", // parameter name
//                                                     16,   // minimum value
//                                                     32768,   // maximum value
//                                                     2048),   // default value
        
        std::make_unique<juce::AudioParameterFloat> ("FFT_Size", // parameterID
                                                     "FFT_Size", // parameter name
                                                     0,   // minimum value
                                                     3,   // maximum value
                                                     1)   // default value
        
    }));
}

int _getFFTSize(int inFFTParameterValue){
    if (inFFTParameterValue == FFTSizes::OneTwentyEight){
        return 128;
    } else if (inFFTParameterValue == FFTSizes::TwoFiftySix){
        return 256;
    } else if (inFFTParameterValue == FFTSizes::FiveTwelve){
        return 512;
    } else if (inFFTParameterValue == FFTSizes::TenTwentyFour){
        return 1024;
    }
};

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Week3PluginAudioProcessor();
}



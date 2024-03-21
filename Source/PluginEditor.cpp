/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Week3PluginAudioProcessorEditor::Week3PluginAudioProcessorEditor (Week3PluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //set universal colors
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::lightblue); //change thumb color
    getLookAndFeel().setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::ghostwhite);
    getLookAndFeel().setColour (juce::Slider::trackColourId, juce::Colours::ghostwhite);
    getLookAndFeel().setColour (juce::Slider::textBoxOutlineColourId, juce::Colour(0,70,70));
    
    
    //Dry Wet SLider
    mDryWetSlider.setRange(0, 1.f);
    mDryWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    mDryWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    addAndMakeVisible(mDryWetSlider);
   // mDryWetSlider.setColour (juce::Slider::thumbColourId, juce::Colour(0,mDryWetSlider.getValue(),mDryWetSlider.getValue()));
    
    mDryWetSliderAttachment.reset (new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.getVTS(),
                                                                                            "dry_wet",
                                                                                             mDryWetSlider));
    //Dry Wet Label
    addAndMakeVisible (DryWetLabel);
            DryWetLabel.setText ("DryWet", juce::dontSendNotification);
            DryWetLabel.attachToComponent (&mDryWetSlider, true); // [4]
            DryWetLabel.setJustificationType(juce::Justification::bottom);
    
    //Blur Slider
    mBlurSlider.setRange(0, 1.f,0.01);
    mBlurSlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 50, 20);
    mBlurSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(mBlurSlider);
    
    mBlurSliderAttachment.reset (new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.getVTS(),
                                                                                             "blur",
                                                                                             mBlurSlider));
    //Blur Label
    addAndMakeVisible (BlurLabel);
            BlurLabel.setText ("Spectral Blur", juce::dontSendNotification);
            BlurLabel.attachToComponent (&mBlurSlider, false); // [4]
            BlurLabel.setJustificationType(juce::Justification::topRight);
    
    //Gate Slider
    mGateSlider.setRange(0, 1.f,0.01);
    mGateSlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 50, 20);
    mGateSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(mGateSlider);
    
    mGateSliderAttachment.reset (new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.getVTS(),
                                                                                             "gate",
                                                                                             mGateSlider));
    //Gate Label
    addAndMakeVisible (GateLabel);
            GateLabel.setText ("Spectral Gate", juce::dontSendNotification);
            GateLabel.attachToComponent (&mGateSlider, false); // [4]
            GateLabel.setJustificationType(juce::Justification::topRight);
    
    
    //pitch Slider
    mPitchSlider.setRange(0, 1.f,0.01);
    mPitchSlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 50, 20);
    mPitchSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(mPitchSlider);
    mPitchSlider.setDoubleClickReturnValue(true, 0.5);
    
    mPitchSliderAttachment.reset (new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.getVTS(),
                                                                                             "pitchShift",
                                                                                             mPitchSlider));

    //pitch Label
    addAndMakeVisible (PitchLabel);
            PitchLabel.setText ("Pitch Shift", juce::dontSendNotification);
            PitchLabel.attachToComponent (&mPitchSlider, false); // [4]
            PitchLabel.setJustificationType(juce::Justification::topRight);
    
    
    //FFT Size Slider
    mFFTSizeSlider.setRange(16, 32768, 16);
    mFFTSizeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    mFFTSizeSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    //addAndMakeVisible(mFFTSizeSlider);
    mFFTSizeSlider.setDoubleClickReturnValue(true, 2048);
    
    mFFTSizeSliderAttachment.reset (new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.getVTS(),
                                                                                             "FFTSize",
                                                                                             mFFTSizeSlider));
    
    //FFT Size Label
    addAndMakeVisible (FFTSizeLabel);
            FFTSizeLabel.setText ("FFT Size", juce::dontSendNotification);
            FFTSizeLabel.attachToComponent (&mFFTSizeDropdown, true); // [4]
            FFTSizeLabel.setJustificationType(juce::Justification::centredTop);
        
    
    //****REDUCTION****///
    //Reduction Slider
    mReductionSlider.setRange(0, 1.f,0.01);
    mReductionSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 64, 20);
    mReductionSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    addAndMakeVisible(mReductionSlider);
    mReductionSliderAttachment.reset (new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.getVTS(),
                                                                                           "Reduction",
                                                                           mReductionSlider));
    mReductionSlider.setDoubleClickReturnValue(true, 0.5);
    //mReductionSlider.setColour (juce::Slider::thumbColourId, juce::Colour(0,mDryWetSlider.getValue(),mDryWetSlider.getValue()));
    // Reduction Label
    addAndMakeVisible (ReductionLabel);
            ReductionLabel.setText ("Reduction", juce::dontSendNotification);
            ReductionLabel.attachToComponent (&mReductionSlider, false); // [4]
    ReductionLabel.setJustificationType(juce::Justification::centredTop);
                     
    
    //HarmVsNoise SLider
//    mHarmVsNoiseSlider.setRange(0,1.f);
//    mHarmVsNoiseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
//    addAndMakeVisible(mHarmVsNoiseSlider);
//    mHarmVsNoiseSliderAttachment.reset (new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.getVTS(),
//
//                                                                                           "harmVsNoise",
//                                                                                           mHarmVsNoiseSlider));
    
    //harmVsNoise Button
    HarmVsNoiseButton.setClickingTogglesState(true);
    HarmVsNoiseButton.onClick = [&]()
    {
        const auto message = HarmVsNoiseButton.getToggleState() ? "DeNoise" : "DeHarm";
        printf(message);
        HarmVsNoiseButton.setButtonText(message);
    };
    HarmVsNoiseButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::lightblue);
    HarmVsNoiseButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour(0,100,127));
    addAndMakeVisible(HarmVsNoiseButton);
    mHarmVsNoiseButtonAttachment.reset (new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.getVTS(),
                                                                                                  
                                                                                           "harmVsNoise",
                                                                                           mHarmVsNoiseSlider));
    
    
    // HarmVsNoise Label
    addAndMakeVisible (HarmVsNoiseLabel);
            HarmVsNoiseLabel.setText ("Harmonic Vs Noise", juce::dontSendNotification);
            HarmVsNoiseLabel.attachToComponent (&mHarmVsNoiseSlider, true); // [4]
                                                                                                
    //FFT Size Dropdown
   //mFFTSizeDropdown.reset(new juce::ComboBox());
    mFFTSizeDropdown.addItem("128", 1);
    mFFTSizeDropdown.addItem("256", 2);
    mFFTSizeDropdown.addItem("512", 3);
    mFFTSizeDropdown.addItem("1024", 4);
    mFFTSizeDropdown.addItem("2048",5);
    mFFTSizeDropdown.addItem("4096",6);
    mFFTSizeDropdown.addItem("8192",7);
    addAndMakeVisible(mFFTSizeDropdown);
    
    mFFTSizeDropdownAttachment.reset (new juce::AudioProcessorValueTreeState::ComboBoxAttachment (audioProcessor.getVTS(), "FFT_Size", mFFTSizeDropdown));
         
    
    
    
    
    setResizable(true, true);
    getConstrainer()->setFixedAspectRatio(2.0);
    setResizeLimits (500,250,1500,750);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 250);
}

Week3PluginAudioProcessorEditor::~Week3PluginAudioProcessorEditor()
{
}

//==============================================================================
void Week3PluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::black);
    setOpaque(false);
    g.setFont (juce::Font());
}

void Week3PluginAudioProcessorEditor::resized()
{
    
    //margin variables
    auto marginTop = getHeight()*0.04;
    auto marginLeft = getWidth()*0.01;
    auto marginBottom = getHeight()*0.04;
    auto marginRight = getWidth()*0.001;
    
    //component variables
    auto reductionWidth = getWidth()*0.35;
    auto buttonWidth = getWidth() * 0.2;
    auto buttonHeight = buttonWidth * 0.3;
    auto sliderSpacing = getHeight() * 0.2;
    auto drywetWidth = getWidth()*0.17;
    auto FFTSliderWidth = getWidth()*0.15;
    
    //Reduction Slider
    mReductionSlider.setBounds(marginLeft, marginTop, reductionWidth, reductionWidth);

    //blur Slider
 mBlurSlider.setBounds(mReductionSlider.getX() + mReductionSlider.getWidth() + marginLeft, marginTop*3, getWidth() - mBlurSlider.getX() - marginRight,20);

    //Gate Slider
    mGateSlider.setBounds(mReductionSlider.getX() + mReductionSlider.getWidth() + marginLeft, marginTop*3 + sliderSpacing, getWidth() - mGateSlider.getX() - marginRight,20);

    //Pitch slider
    mPitchSlider.setBounds(mReductionSlider.getX() + mReductionSlider.getWidth() + marginLeft, marginTop*3 + sliderSpacing*2, getWidth() - mPitchSlider.getX() - marginRight,20);
    
    //Dry/Wet Slider
    mDryWetSlider.setBounds(getWidth() - drywetWidth - marginRight,getHeight() - drywetWidth - marginBottom , drywetWidth, drywetWidth);
    
    //FFT Size Slider
    mFFTSizeSlider.setBounds(mDryWetSlider.getX()-FFTSliderWidth*2,mDryWetSlider.getY(),drywetWidth,drywetWidth);
    
    //FFT Size Slider
    mFFTSizeDropdown.setBounds(mDryWetSlider.getX()-FFTSliderWidth*2,mPitchSlider.getY()+marginTop*6,drywetWidth,drywetWidth/3);
    
    
    
//    mDryWetSlider.setSize(getWidth()/5,getWidth()/5);
//    mDryWetSlider.setCentrePosition(getWidth()-getWidth()/5,getHeight()-getHeight()/4);
    
    
    //mBlurSlider.setBounds(getWidth()/4 * 2, 0, getWidth()/4, getHeight());
   // mHarmVsNoiseSlider.setBounds(getWidth()/4 * 3, 0, getWidth()/4, getHeight());
    
    /*
    mDryWetSlider.setBounds(0, 0, getWidth()/4, getHeight()- (getHeight()/5));
    mBlurSlider.setBounds(getWidth()/4, 0, getWidth()/4, getHeight());
    mReductionSlider.setBounds(getWidth()/4 * 2, 0, getWidth()/4, getHeight());
    mHarmVsNoiseSlider.setBounds(getWidth()/4 * 3, 0, getWidth()/4, getHeight());
    */
    //setOpaque(false);
    //harmvsnoise
//    HarmVsNoiseButton.setBounds(mReductionSlider.getX()+25,mReductionSlider.getY() + mReductionSlider.getWidth() + marginLeft, buttonWidth, buttonHeight);
    HarmVsNoiseButton.setBounds(mReductionSlider.getWidth()/2 - buttonWidth/2 + marginLeft,mReductionSlider.getY() + mReductionSlider.getWidth() + marginLeft*4, buttonWidth, buttonHeight);
}

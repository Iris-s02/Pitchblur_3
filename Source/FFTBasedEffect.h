/*
  ==============================================================================

    RealTimeFFT.h
    Created: 20 Mar 2024 1:51:39am
    Author:  soli rosenthal

  ==============================================================================
*/

#pragma once

class realTimeFFT {
public:
    //constructor
    realTimeFFT();
    
    //destructor
    ~realTimeFFT();
    
    void prepareToPlay(float inSampleRate);
    
    //void processBlock(juce::AudioBuffer<float>& inBuffer);
    
    
    float getNextSample();
    
    void setParameters();
    
private:
    
    //juce::dsp::FFT mFFT;
    
    void _wrapPosition(int& inValue);
    
    int writeHead = 0;
    
   // juce::AudioBuffer<float>& mCircularBuffer;
    
    
    
    
    
    
};

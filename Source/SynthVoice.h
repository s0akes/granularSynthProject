/*
  ==============================================================================

    SynthVoice.h
    Created: 15 Nov 2022 4:00:20pm
    Author:  (s) Daniel G Jones (smells lol)

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "waveTableClass.h"
#include <vector>
#include "grain.h"
#include "Distortion.h"

//randomly trigger a grain
//every sample check grain::isActive() 
//if it is acitve grain::getNextSample
//repeat for every grain in the vector
//add the samples together
//output to buffer
//done :)


//Dan's job is to triggering grains in renderNextBlock and add to the output buffer

class SynthVoice : public juce::SynthesiserVoice, 
    public juce::AudioProcessorValueTreeState::Listener // [3] Create voice class
{
public:
    SynthVoice(juce::AudioProcessorValueTreeState* valueTreeState);

    bool  canPlaySound(juce::SynthesiserSound* sound) override;

    void  startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;

    void  stopNote(float velocity, bool allowTailOff) override;

    void  pitchWheelMoved(int newPitchWheelValue) override;

    void  controllerMoved(int controllerNumber, int newControllerValue) override;

    void  renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;

    void parameterChanged(const juce::String& parameterID, float newValue) override;
    
    int randomTrigger();//temporarararay

    std::vector<grain> grainStore;

    grainRandomiser randomiser;

private:

    int chance = 0;

    bool foundActive = 0;
    double amplitude = 0;
    double frequency = 0;
    juce::AudioSampleBuffer* waveTablePtr = nullptr;
    // bool ean variable active flag

    juce::ADSR densityEnv;
    juce::ADSR::Parameters densityEnvParams;
    juce::AudioProcessorValueTreeState* ADSRstate;

    grainParams grainParameters;

    Dist waveShaper;

    double temp = 0;
};

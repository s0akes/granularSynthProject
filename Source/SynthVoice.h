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

//randomly trigger a grain store the grain in a vector
//every sample check grain::isActive() 
//if it is acitve grain::getNextSample
//if it is not active then delete the grain
//repeat for every grain in the vector
//add the samples together
//output to buffer
//done :)

class SynthVoice : public juce::SynthesiserVoice // [3] Create voice class
{
public:
    SynthVoice();

    bool  canPlaySound(juce::SynthesiserSound* sound) override;

    void  startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;

    void  stopNote(float velocity, bool allowTailOff) override;

    void  pitchWheelMoved(int newPitchWheelValue) override;

    void  controllerMoved(int controllerNumber, int newControllerValue) override;

    void  renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;

    double getFrequency();

    std::vector<grain> grainStore;

private:

    double amplitude = 0;
    double frequency = 0;
    juce::SynthesiserSound* soundPtr;

    


};
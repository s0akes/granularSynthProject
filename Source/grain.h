/*
  ==============================================================================

    grain.h
    Created: 11 Nov 2022 10:07:55am
    Author:  Mace Noonan

  ==============================================================================
*/


#pragma once
#include <JuceHeader.h>
#include "waveTableClass.h"
#include <random>

class grain
{
public:
    // g1 = new grain(frequecy, randomness, pointer to buffer);
    grain(); 
    
    void startGrain(double frequency, double randomFactor, juce::AudioSampleBuffer* wt, float grainLength); //sets the frequency and the randomness of the grain

    double getNextSample(); //returns the next sample based on the synth

    bool isActive(); //checks if the ADSR is acitve, if it is not then delete the grain

    int randomCent();

private:
    float randomFequency = 440; //the new frequency 
    float delta = 0; //phase shift in samples for the given frequency

    juce::AudioSampleBuffer* waveTablePtr = nullptr; //pointer to the wavetable (to be created seperately to save memory/cpu)

    float attackTime = 0; //time it takes to get to full volume in seconds
    float decayTime = 0; //time it takes to get to 0 volume after attack in seconds
    float length = 0; //full length in seconds (attackTime + decayTime)
    int sampleRate = 44100;
    float currentIndex = 0;
    float amplitude = 1;

    juce::ADSR envelope;
    juce::ADSR::Parameters envParam;
};


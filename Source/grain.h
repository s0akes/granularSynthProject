/*
  ==============================================================================

    grain.h
    Created: 11 Nov 2022 10:07:55am
    Author:  Mace Noonan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class grain
{
public:
    grain(double frequency, double randomFactor, juce::AudioSampleBuffer* wt); //sets the frequency and the randomness of the grain

    double getNextSample(); //returns the next sample based on the synth

private:
    float randomFequency; //the new frequency 
    float delta; //phase shift in samples for the given frequency

    juce::AudioSampleBuffer* waveTable; //pointer to the wavetable (to be created seperately to save memory/cpu)

    float attackTime; //time it takes to get to full volume in seconds
    float decayTime; //time it takes to get to 0 volume after attack in seconds
    float lenght; //full length in seconds (attackTime + decayTime)
};

class waveTable
{
public:
    waveTable(); //this class will be able to manipulate the wavetable to be different waveshapes and will store the waveTable used by the grain

    
};
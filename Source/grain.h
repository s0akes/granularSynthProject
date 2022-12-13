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
#include "Distortion.h"

class grainParams
{
public:
    float frequency; //the frequency
    float grainLength;//full length of the grain
    float grainShape;//ratio 0-1 of where the peak of the envelope will be
    int waveShape;//wave shaping profile int 1-5
    float pan; //0-100 panning of the grain
    Dist* waveShaper;

};

class grain
{
public:
    // g1 = new grain(frequecy, randomness, pointer to buffer);
    grain(); 
    
    void startGrain(grainParams* params, juce::AudioSampleBuffer* wt); //sets the frequency and the randomness of the grain

    double getNextSampleL(); //returns the next sample based on the synth
    double getNextSampleR(); //returns the next sample based on the synth

    bool isActive(); //checks if the ADSR is acitve, if it is not then delete the grain

private:
    double getNextSample(); //returns the next sample based on the synth
    double temp;

    float randomFequency = 440; //the new frequency 
    float delta = 0; //phase shift in samples for the given frequency

    juce::AudioSampleBuffer* waveTablePtr = nullptr; //pointer to the wavetable (to be created seperately to save memory/cpu)

    float attackTime = 0; //time it takes to get to full volume in seconds
    float decayTime = 0; //time it takes to get to 0 volume after attack in seconds
    float length = 0; //full length in seconds (attackTime + decayTime)
    int sampleRate = 44100;
    float currentIndex = 0;
    float amplitude = 0.5;

    grainParams parameters;
    Dist* waveShaper;

    juce::ADSR envelope;
    juce::ADSR::Parameters envParam;
};

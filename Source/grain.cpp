/*
  ==============================================================================

    grain.cpp
    Created: 11 Nov 2022 10:07:55am
    Author:  Mace Noonan

  ==============================================================================
*/

#include "grain.h"
#include <math.h>

grain::grain(double frequency, double randomFactor, juce::AudioSampleBuffer* wt, float grainLength)
{
    //randomise the frequency and attack/decay
    //frequency = frequency + pow(2, randomFactor / 12*100) - 1; //randomFactor is the number of cents deviation
    envParam.attack = 0.1;
    envParam.decay = 0.5;
    envParam.sustain = 0.0;
    envParam.release = 0.0;
    envelope.setParameters(envParam);
    envelope.noteOn();
    
    //find delta based on the new frequency
    delta = wt->getNumSamples() * frequency / sampleRate;

    //set the wavetable
    juce::AudioSampleBuffer* waveTablePtr = wt;
}

double grain::getNextSample()
{
    double V;

    //linear interpolation of the wavetable based on delta
    int tableSize = waveTablePtr->getNumSamples();

    int index0 = (int)currentIndex;
    int index1;
    if (index0 == tableSize - 1)
        index1 = 0;
    else 
        index1 = index0 + 1;
    double frac = currentIndex - (double)index0;
    double V0 = waveTablePtr->getSample(0, index0);
    double V1 = waveTablePtr->getSample(0, index1);
    V = frac * V1 + (1 - frac) * V0; //interpolated value

    V *= amplitude * envelope.getNextSample();

    currentIndex += delta; //advance index
    if (currentIndex >= (double)tableSize) //wrap at the end of the wavetable
        currentIndex -= tableSize;

    //amplitude envelope

    return V; //returns values from wavetable * envelope
}

bool grain::isActive()
{
    return false; //ask georgio about the envelope.isActive and weather to use the attack and release or attack and decay
}

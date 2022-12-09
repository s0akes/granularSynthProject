/*
  ==============================================================================

    grain.cpp
    Created: 11 Nov 2022 10:07:55am
    Author:  Mace Noonan

  ==============================================================================
*/

#include "grain.h"
#include <math.h>

grain::grain()
{

}

void grain::startGrain(grainParams params, juce::AudioSampleBuffer* wt)
{
    parameters = params;
    //set the frequency and attack/decay
    envParam.attack = params.grainLength*params.grainShape;
    envParam.decay = 0.0;
    envParam.sustain = 1.0;
    envParam.release = params.grainLength*(1-params.grainShape);
    envelope.setParameters(envParam);
    envelope.noteOn();
    
    //find delta based on the new frequency
    delta = wt->getNumSamples() * params.frequency / sampleRate;

    //set the wavetable
    waveTablePtr = wt;
}

double grain::getNextSampleL()
{
    temp = getNextSample();
    return temp * parameters.pan;
}

double grain::getNextSampleR()
{
    return temp * (1-parameters.pan);
}

double grain::getNextSample()
{
    double V;

    //linear interpolation of the wavetable based on delta
    int tSize = waveTablePtr->getNumSamples();

    int index0 = (int)currentIndex;
    int index1;

    if (index0 >= tSize - 1 || index0 < 0) 
    {
        index1 = 0;
    }
    else 
    {
        index1 = index0 + 1;
    }

    double frac = currentIndex - (double)index0;
    double V0 = waveTablePtr->getSample(0, index0);
    double V1 = waveTablePtr->getSample(0, index1);
    V = frac * V1 + (1 - frac) * V0; //interpolated value

    V *= amplitude * (double)envelope.getNextSample();
    if (envelope.getNextSample() > 0.99)
    {
        envelope.noteOff();
    }

    currentIndex = currentIndex + delta; //advance index
    if (currentIndex >= (double)tSize) //wrap at the end of the wavetable
        currentIndex -= tSize;

    //amplitude envelope

    return V; //returns values from wavetable * envelope
}

bool grain::isActive()
{
    return envelope.isActive(); //returns false once envelope release phase is over, envlope is started in the constructor
}

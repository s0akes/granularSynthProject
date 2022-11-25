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

void grain::startGrain(double frequency, double randomFactor, juce::AudioSampleBuffer* wt, float grainLength)
{
    //randomise the frequency and attack/decay
    int c = randomCent();
    //frequency = frequency + pow(2, c / (12*100)) - 1; //randomFactor is the number of cents deviation
    envParam.attack = 0.0;
    envParam.decay = 0.0;
    envParam.sustain = 1.0;
    envParam.release = 1.0;
    envelope.setParameters(envParam);
    envelope.noteOn();
    
    //find delta based on the new frequency
    delta = wt->getNumSamples() * frequency / sampleRate;

    //set the wavetable
    waveTablePtr = wt;
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

int grain::randomCent()
{
    return rand() % 100 - 50;
}

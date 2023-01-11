/*
  ==============================================================================

    grain.cpp
    Created: 11 Nov 2022 10:07:55am
    Author:  Mace Noonan

  ==============================================================================
*/

#include "grain.h"
#include <math.h>
#include <random>

grain::grain()
{
    envelope.reset();
}

void grain::startGrain(grainParams* params, juce::AudioSampleBuffer* wt)
{
    parameters = *params;
    //set the frequency and attack/decay
    envParam.attack = 0.005 + parameters.grainLength * parameters.grainShape;
    envParam.decay = 0.1;
    envParam.sustain = 1;
    envParam.release = 0.005 + parameters.grainLength * (1 - parameters.grainShape);
    envelope.setParameters(envParam);
    envelope.noteOn();
    
    //find delta based on the new frequency
    delta = wt->getNumSamples() * parameters.frequency / sampleRate;

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

    V *= parameters.grainVolume * (double)envelope.getNextSample();
    if (envelope.getNextSample() > 0.99)
    {
        envelope.noteOff();
    }

    currentIndex = currentIndex + delta; //advance index
    if (currentIndex >= (double)tSize) //wrap at the end of the wavetable
        currentIndex -= tSize;

    //V = parameters.waveShaper->distort(V);  // Not in use currently but can be used if desired

    V = V * parameters.grainControlVolume;//amplitude for cloud to control overall volume

    return V; //returns values from wavetable * envelope
}

bool grain::isActive()
{
    return envelope.isActive(); //returns false once envelope release phase is over, envlope is started in the constructor
}

grainParams grainRandomiser::randomise(grainParams* params, double r)
{
    grainParams output = *params;

    output.frequency = frequency(output.frequency, r);
    output.grainLength = grainLength(output.grainLength, r);
    output.grainShape = grainShape();
    output.pan = pan();
    output.grainVolume = grainVolume();

    return output;
}

bool grainRandomiser::randomTrigger()
{
    int temp = rand() % triggerChance;
    if (temp == 1006)
        return true;
    else
        return false;
}

float grainRandomiser::frequency(float f, double r)
{
    float random = (rand() % 100) - 50;
    f = f + pow(2, (r * random * 50) / 1200);
    return f;
}

float grainRandomiser::grainLength(float l, double r)
{
    float random = ((float)(rand() % 100) / 100);
    l += random;
    return l;
}

float grainRandomiser::grainShape()
{
    float random = (((float)(rand() % 100) / 100) * 0.8) + 0.1;
    return random;
}

float grainRandomiser::pan()
{
    float random = (float)(rand() % 100)/100;
    return random;
}

float grainRandomiser::grainVolume()
{
    float random = (float)(rand() % 100) / 100;
    return random;
}

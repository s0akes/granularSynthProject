/*
  ==============================================================================

    grain.cpp
    Created: 11 Nov 2022 10:07:55am
    Author:  Mace Noonan

  ==============================================================================
*/

#include "grain.h"

grain::grain(double frequency, double randomFactor, juce::AudioSampleBuffer* wt)
{
    //randomise the frequency and attack/decay

    //find delta based on the new frequency

    //set the wavetable
}

double grain::getNextSample()
{
    //linear interpolation of the wavetable based on delta

    //amplitude envelope

    return 0.0; //returns values from wavetable * envelope
}

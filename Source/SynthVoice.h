/*
  ==============================================================================

    SynthVoice.h
    Created: 15 Nov 2022 4:00:20pm
    Author:  (s) Daniel G Jones (smells lol)

  ==============================================================================
*/

#pragma once

//randomly trigger a grain store the grain in a vector
// every sample check grain::isActive() 
// if it is acitve grain::getNextSample
//repeat for every grain in the vector
//add the samples together
//output to buffer
//done :)

#include <JuceHeader.h>
#include "waveTableClass.h"

public:

synthVoice(double frequency, int amplitude, double duration);


private:

juce::AudioSampleBuffer* WT = nullptr;
double delta = 0;
double currentIndex = 0;
double amplitude = 0;

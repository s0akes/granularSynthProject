/*
  ==============================================================================

    SynthVoice.h
    Created: 15 Nov 2022 4:00:20pm
    Author:  (s) Daniel G Jones

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "waveTableClass.h"

public:

synthVoice(double frequency, int amplitude, double duration);


private:

juce::AudioSampleBuffer* WT = nullptr;
double delta = 0;
double currentIndex = 0;
double amplitude = 0;
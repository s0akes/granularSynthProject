/*
  ==============================================================================

    SynthVoice.h
    Created: 15 Nov 2022 4:00:20pm
    Author:  (s) Daniel G Jones (smells lol)

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "waveTableClass.h"

//randomly trigger a grain store the grain in a vector
//every sample check grain::isActive() 
//if it is acitve grain::getNextSample
//if it is not active then delete the grain
//repeat for every grain in the vector
//add the samples together
//output to buffer
//done :)

class synthVoice {
public:

  void  synthVoice (double freq, int ampl, double time) override;

  bool  canPlaySound (juce::SynthesiserSound * sound) override;
    
  void  startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    
  void  stopNote (float velocity, bool allowTailOff) override;
    
  void  renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;

private:

  juce::AudioSampleBuffer* WT = nullptr; //wavetable pointer
  double delta = 0; // delta angle from freq and sr
  double currentIndex = 0; // index for wavetable playback
  double ampl = 0;

};

/*
  ==============================================================================

    SynthVoice.cpp
    Created: 15 Nov 2022 4:00:12pm
    Author:  (s) Daniel G Jones

  ==============================================================================
*/

#include "SynthVoice.h"
#include <vector>

SynthVoice::SynthVoice()
{


  for(int i = 0; i < grainStore.size() - 1; i++){
      
    grain::grain(frequency, 0, soundPtr->getWaveTablePtr, 0);

    
}

}

bool  SynthVoice::canPlaySound(juce::SynthesiserSound* sound) 
{
  
}

void  SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) 
{
    soundPtr = sound;
    frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);

    
    
    


}

void  SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    amplitude = 0.0;
    clearCurrentNote();
}

void  SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void  SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void  SynthVoice::renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) 
{

}

double getFrequency()
{
    return frequency;
}




//randomly trigger a grain store the grain in a vector
//every sample check grain::isActive() 
//if it is acitve grain::getNextSample
//if it is not active then delete the grain
//repeat for every grain in the vector
//add the samples together
//output to buffer
//done :)
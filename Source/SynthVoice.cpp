/*
  ==============================================================================

    SynthVoice.cpp
    Created: 15 Nov 2022 4:00:12pm
    Author:  (s) Daniel G Jones

  ==============================================================================
*/

#include "SynthVoice.h"

sinVoice::sinVoice()
{
    
}

bool  sinVoice::canPlaySound(juce::SynthesiserSound* sound) // [6]
{

}

void  sinVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) // [7]
{

}

void  sinVoice::stopNote(float velocity, bool allowTailOff) // [8]
{

}

void  sinVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void  sinVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void  sinVoice::renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) // [9]
{

    }
}




//randomly trigger a grain store the grain in a vector
//every sample check grain::isActive() 
//if it is acitve grain::getNextSample
//if it is not active then delete the grain
//repeat for every grain in the vector
//add the samples together
//output to buffer
//done :)
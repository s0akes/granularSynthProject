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
    densityEnv.setSampleRate(getSampleRate());

    for (int i = 0; i < 100; i++)
    {
    grainStore.push_back(grain());
    }

}

bool  SynthVoice::canPlaySound(juce::SynthesiserSound* sound) 
{
    
}

void  SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) 
{
    soundPtr = sound;
    frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);

    densityEnvParams.attack = 0.5;
    densityEnvParams.decay = 0.5;
    densityEnvParams.sustain = 0.5;
    densityEnvParams.release = 0.5;
    densityEnv.setParameters(densityEnvParams);
    densityEnv.noteOn();
    
    


}

void  SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    if (densityEnv.getNextSample() < (1./5 * getSampleRate())) {

        for (int i = 0; i < grainStore.size() - 1; i++) {

            
            bool activeGrain = 1;
            if (grainStore[i].isActive()) {

                activeGrain = 0;

                if (!activeGrain)
                    clearCurrentNote();
                    amplitude = 0.0;
               
            }

    }
 }
    
    if (!allowTailOff || !densityEnv.isActive())
    {
        clearCurrentNote();
    }
    else
    {
        densityEnv.noteOff();
    }
}

void  SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
    const int wheelPos = m.getPitchWheelValue();
        lastPitchWheelValues [channel - 1] = wheelPos;
        handlePitchWheel (channel, wheelPos);
}

void  SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    for (int i = 0; i < grainStore.size(); i++) {
        if (grainStore[i].isActive()) 
        {
            temp = grainStore[i].getNextSample(); 
        }

        for (int j = 0; j < outputBuffer.getNumChannels(); j++)
        {
            outputBuffer.addSample(j, i, temp);
        }
        

        if (!densityEnv.isActive())
        {
            clearCurrentNote();
        }

    }
}
double SynthVoice::getFrequency()
{
    return frequency;
}




//randomly trigger a grain
//every sample check grain::isActive() 
//if it is acitve grain::getNextSample
//repeat for every grain in the vector
//add the samples together
//output to buffer
//done :)

/*
  ==============================================================================

    SynthVoice.cpp
    Created: 15 Nov 2022 4:00:12pm
    Author:  (s) Daniel G Jones

  ==============================================================================
*/

#include "SynthVoice.h"
#include <vector>

SynthVoice::SynthVoice(juce::AudioProcessorValueTreeState* valueTreeState)
{
    densityEnv.setSampleRate(getSampleRate());

    for (int i = 0; i < 10; i++)
    {
        grainStore.push_back(grain());
    }

}

bool  SynthVoice::canPlaySound(juce::SynthesiserSound* sound) 
{
    return true;
}

void  SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) 
{
    waveTablePtr = &(dynamic_cast<waveTableClass*>(sound)->waveTable);
    getFrequency(midiNoteNumber);

    densityEnvParams.attack = 0.1;
    densityEnvParams.decay = 0.1;
    densityEnvParams.sustain = 0.4;
    densityEnvParams.release = 0.1;
    densityEnv.setParameters(densityEnvParams);
    densityEnv.noteOn();


}

void  SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    if (densityEnv.getNextSample() < (1./getSampleRate())) {

        for (int i = 0; i < grainStore.size() - 1; i++) {
                        
            bool activeGrain = 1;

            if (grainStore[i].isActive()) {

                activeGrain = 0;

                if (activeGrain == 1)
                    clearCurrentNote();
                    densityEnv.reset();
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
    //const int wheelPos = m.getPitchWheelValue();
    //lastPitchWheelValues[channel - 1] = wheelPos;
    //handlePitchWheel(channel, wheelPos);
}

void  SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (!this->isVoiceActive())
        return;

    

    
        /*if (grainStore[i].isActive()) 
        {
            temp = grainStore[i].getNextSample(); 
        }

        temp = temp * densityEnv.getNextSample();*/

        
    for (int s = startSample; s < numSamples + startSample; s++)
    {

        if (counter >= 44100)//temporary function to randomly trigger grain
        {
            counter = 0;
            for (int i = 0; i < grainStore.size(); i++)//finds the first active grain and starts playing it
            {
                if (!grainStore[i].isActive())
                {
                    grainStore[i].startGrain(frequency, 0, waveTablePtr, 0);
                    break;
                }
            }
        }

        for (int i = 0; i < grainStore.size(); i++) {

            if (grainStore[i].isActive())
            {
                temp = grainStore[i].getNextSample();
                //temp = temp * densityEnv.getNextSample();
                outputBuffer.addSample(0, s, temp);
                

            }
            

        }

        counter += 1;
                
    }
        

    if (!densityEnv.isActive())
    {
        clearCurrentNote();
    }

}
double SynthVoice::getFrequency(int midiNoteNumber)
{
    frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    return frequency;
}

int SynthVoice::randomTrigger()
{
    return rand() % 20;
}




//randomly trigger a grain
//every sample check grain::isActive() 
//if it is acitve grain::getNextSample
//repeat for every grain in the vector
//add the samples together
//output to buffer
//done :)

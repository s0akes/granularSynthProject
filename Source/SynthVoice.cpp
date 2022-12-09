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

    for (int i = 0; i < 100; i++)
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
    //getFrequency(midiNoteNumber);

    frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    
    
    densityEnvParams.attack = 0.;
    densityEnvParams.decay = 1.;
    densityEnvParams.sustain = 0.75;
    densityEnvParams.release = 5.;
    densityEnv.setParameters(densityEnvParams);
    densityEnv.noteOn();
    amplitude = velocity;

}

void  SynthVoice::stopNote(float velocity, bool allowTailOff)
{

    if (!allowTailOff)
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

    float density = amplitude * 500 / 44100.;
    
    for (int s = startSample; s < numSamples + startSample; s++)
    {
        float currentEnvValue = densityEnv.getNextSample();
        
        if (juce::Random::getSystemRandom().nextFloat() < density * currentEnvValue)
        
        {
            for (int i = 0; i < grainStore.size(); i++)//finds the first active grain and starts playing it
            {
                if (!grainStore[i].isActive())
                {
                    // pp = rand1.randomise(param)
                    // pp = rand2.ransomise(pp)
                    // grainStore[i].startGrain(pp, waveTablePtr);
                    
                    float f = frequency + (2.*juce::Random::getSystemRandom().nextFloat() -1. )* frequency / 100;
                    
                    grainStore[i].startGrain(f, 0, waveTablePtr, 0);
                    
                    break;
                }
            }
        }
        temp = 0;
        for (int i = 0; i < grainStore.size(); i++)
        {

            if (grainStore[i].isActive())
            {
                temp += grainStore[i].getNextSample() ;
            }
            
        }
        //temp *= currentEnvValue * 0.1;
        temp *= 0.05;
        outputBuffer.addSample(0, s, temp);

        counter += 1;
                
    }
        

    if (!densityEnv.isActive())
    {
        
        bool activeGrain = 0;

        for (int i = 0; i < grainStore.size() - 1; i++)
        {
            
            
            if (grainStore[i].isActive())
            {
                
                activeGrain = 1;
                break;

            }
            
        }
        if (activeGrain == 0)
        {
            clearCurrentNote();
            densityEnv.reset();
            amplitude = 0.0;
        }
        
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

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
    ADSRstate = valueTreeState;

    ADSRstate->addParameterListener("ATTACK", this);
    ADSRstate->addParameterListener("DECAY", this);
    ADSRstate->addParameterListener("RELEASE", this);
    ADSRstate->addParameterListener("SUSTAIN", this);

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

    densityEnvParams.attack = 0.1;
    densityEnvParams.decay = 0.1;
    densityEnvParams.sustain = 0.4;
    densityEnvParams.release = 0.1;
    densityEnv.setParameters(densityEnvParams);
    densityEnv.noteOn();

    auto rawAttack = ADSRstate->getRawParameterValue("ATTACK");
    auto rawDecay = ADSRstate->getRawParameterValue("DECAY");
    auto rawSustain = ADSRstate->getRawParameterValue("SUSTAIN");
    auto rawRelease = ADSRstate->getRawParameterValue("RELEASE");
    
    densityEnvParams.attack = rawAttack->load();
    densityEnvParams.decay = rawDecay->load();
    densityEnvParams.sustain = rawSustain->load();
    densityEnvParams.release = rawRelease->load();
    //updates envelope
    densityEnv.setParameters(densityEnvParams);


    grainParameters.frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    grainParameters.grainLength = 2;
    grainParameters.grainShape = 0.5;
    grainParameters.pan = 50;
    grainParameters.waveShaper = 1;
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
        //densityEnv.getNextSample();
        if (counter >= 44100)//temporary function to randomly trigger grain
        {
            counter = 0;
            for (int i = 0; i < grainStore.size(); i++)//finds the first active grain and starts playing it
            {
                if (!grainStore[i].isActive())
                {
                    //randomise parameteres, return new param object
                    grainStore[i].startGrain(grainParameters, waveTablePtr); //this takes the base grainParams untill the random functon is created
                    break;
                }
            }
        }

        for (int i = 0; i < grainStore.size(); i++) {

            if (grainStore[i].isActive())
            {
                outputBuffer.addSample(0, s, grainStore[i].getNextSampleL());
                outputBuffer.addSample(1, s, grainStore[i].getNextSampleR());
            }            
        }
        counter += 1;               
    }
        

    if (!densityEnv.isActive())
    {
        clearCurrentNote();
    }

}

int SynthVoice::randomTrigger()
{
    return rand() % 20;
}

void SynthVoice::parameterChanged(const juce::String& parameterID, float newValue) 
{
    if (parameterID == "ATTACK")
    {
        densityEnvParams.attack = newValue;

    }
    else if (parameterID == "DECAY")
    {
        densityEnvParams.decay = newValue;

    }
    else if (parameterID == "SUSTAIN")
    {
        densityEnvParams.sustain = newValue;

    }
    else if (parameterID == "RELEASE")
    {
        densityEnvParams.release = newValue;

    }

    densityEnv.setParameters(densityEnvParams);
}


//randomly trigger a grain
//every sample check grain::isActive() 
//if it is acitve grain::getNextSample
//repeat for every grain in the vector
//add the samples together
//output to buffer
//done :)

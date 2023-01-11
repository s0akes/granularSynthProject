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
    ADSRstate->addParameterListener("GRAINLENGTH", this);

    for (int i = 0; i < 1000; i++)
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

    //densityEnvParams.attack = 0.1;
    //densityEnvParams.decay = 0.1;
    //densityEnvParams.sustain = 0.4;
    //densityEnvParams.release = 0.1;
    //densityEnv.setParameters(densityEnvParams);
    densityEnv.noteOn();

    auto rawAttack = ADSRstate->getRawParameterValue("ATTACK");
    auto rawDecay = ADSRstate->getRawParameterValue("DECAY");
    auto rawSustain = ADSRstate->getRawParameterValue("SUSTAIN");
    auto rawRelease = ADSRstate->getRawParameterValue("RELEASE");
    
    densityEnvParams.attack = rawAttack->load();
    densityEnvParams.decay = rawDecay->load();
    densityEnvParams.sustain = rawSustain->load();
    //densityEnvParams.release = rawRelease->load();
    //updates envelope
    densityEnv.setParameters(densityEnvParams);


    grainParameters.frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    grainParameters.grainLength = ADSRstate->getRawParameterValue("GRAINLENGTH")->load();
    grainParameters.grainShape = 0.5;
    grainParameters.pan = 0.5;
    grainParameters.waveShape = 2;
    grainParameters.waveShaper = &waveShaper;
    waveShaper.SetDistProfile(grainParameters.waveShape, 10);
}

void  SynthVoice::stopNote(float velocity, bool allowTailOff)
{
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
        
    for (int s = startSample; s < numSamples + startSample; s++)
    {
        densityEnv.getNextSample();
        //randomiser.triggerChance = randomiser.triggerChance * (1.5-(densityEnv.getNextSample()));
        if ((rand() % 44100) == 1)//temporary function to randomly trigger grain
        {
            for (int i = 0; i < grainStore.size(); i++)//finds the first active grain and starts playing it
            {

                //if (!grainStore[i].isActive() && densityEnv.isActive() == 1)
                if (!grainStore[i].isActive())
                {
                    grainParams myParams = randomiser.randomise(&grainParameters, 1);
                    //grainStore[i].startGrain(&randomiser.randomise(&grainParameters, 1), waveTablePtr); //this takes the base grainParams untill the random functon is created
                    grainStore[i].startGrain(&myParams, waveTablePtr);
                    //grainStore[i].startGrain(&grainParameters, waveTablePtr);
                    break;
                }
            }
        }
        foundActive = 0;
        tempBufferL = 0;
        tempBufferR = 0;
        for (int j = 0; j < grainStore.size(); j++) {

            if (grainStore[j].isActive())
            {
                //outputBuffer.addSample(0, s, waveShaper.SoftClip(grainStore[j].getNextSampleL()));
                //outputBuffer.addSample(1, s, waveShaper.SoftClip(grainStore[j].getNextSampleR()));
                //outputBuffer.addSample(0, s, grainStore[j].getNextSampleL());
                //outputBuffer.addSample(1, s, grainStore[j].getNextSampleR());

                tempBufferL += grainStore[j].getNextSampleL();
                tempBufferR += grainStore[j].getNextSampleR();

                foundActive += 1;
            }
        }

        outputBuffer.addSample(0, s, tempBufferL);
        outputBuffer.addSample(1, s, tempBufferR);

        if (foundActive == 0 && !densityEnv.isActive())
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
    //
    //if (!densityEnv.isActive())
    //{
    //    clearCurrentNote();
    //}

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

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "grain.h"
#include "waveTableClass.h"

class GranularSynthProjectAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    GranularSynthProjectAudioProcessor();
    ~GranularSynthProjectAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void fillDelayBuffer(int channel, int bufferLength, int delayBufferLength, const float* bufferData, const float* delayBufferData);
    void getFromDelayBuffer(juce::AudioBuffer<float>& buffer, int channel, int bufferLength, int delayBufferLength, const float* bufferData, const float* delayBufferData);
    void feedback(int channel, int bufferLength, int delayBufferLength, float* dryBuffer);

    juce::AudioProcessorValueTreeState parameterTree;

private:

    juce::Synthesiser synth; //this is the synth object that holds all the voices and the sounds!!!! >>VERY IMPORTANT<<

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    juce::AudioBuffer<float> delayBuffer;
    int delayWritePointer = 0;
    int samplerRate;
   
    // delay parameters
    int delayTime = 100;
    float feedbackRate = 0.8;
    float wetMix = 1.0;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularSynthProjectAudioProcessor)
};

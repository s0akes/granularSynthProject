/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>
#include "SynthVoice.h"

//==============================================================================
GranularSynthProjectAudioProcessor::GranularSynthProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), parameterTree(*this, nullptr, "Parameters", createParameterLayout())
#endif
{
    synth.addSound(new waveTableClass()); //wavetableclass is the synthesiser sound
    
    for (auto i = 0; i < 16; ++i) // create 4 voice polyphony by adding 4 voices to the synth object
        synth.addVoice (new SynthVoice(&parameterTree)); //voices are destroyed by the synth when not needed
}

GranularSynthProjectAudioProcessor::~GranularSynthProjectAudioProcessor()
{
}

//==============================================================================
const juce::String GranularSynthProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GranularSynthProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GranularSynthProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GranularSynthProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GranularSynthProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GranularSynthProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GranularSynthProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GranularSynthProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String GranularSynthProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void GranularSynthProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void GranularSynthProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void GranularSynthProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GranularSynthProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void GranularSynthProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    buffer.clear();
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    //juce::ScopedNoDenormals noDenormals;
    //auto totalNumInputChannels  = getTotalNumInputChannels();
    //auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    //for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    //    buffer.clear (i, 0, buffer.getNumSamples());

   
    //for (int channel = 0; channel < totalNumInputChannels; ++channel)
    //{
    //    auto* channelData = buffer.getWritePointer (channel);

       
    //}
}

//==============================================================================
bool GranularSynthProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* GranularSynthProjectAudioProcessor::createEditor()
{
    return new GranularSynthProjectAudioProcessorEditor (*this);
}

//==============================================================================
void GranularSynthProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    juce::ValueTree state = parameterTree.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);

}

void GranularSynthProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes)); // [PP 4.2]
    if (xmlState.get() != nullptr && xmlState->hasTagName(parameterTree.state.getType()))
        parameterTree.replaceState(juce::ValueTree::fromXml(*xmlState)); // [PP 4.3]
}

juce::AudioProcessorValueTreeState::ParameterLayout GranularSynthProjectAudioProcessor::createParameterLayout()
{
    // Here the NormalisableRange will be set for each parameter
    // Params will then be pushed back with smart pointers

    juce::NormalisableRange<float> attackRange(0., 3., 0.001, 0.5);
    juce::NormalisableRange<float> decayRange(0., 3., 0.001, 0.5);
    juce::NormalisableRange<float> releaseRange(0., 3., 0.001, 0.5);

    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", attackRange, 0.2f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", decayRange, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", releaseRange, 1.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("GRAINLENGTH", "Grain Length", 1, 10, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DELAYTIME", "Delay Time", 20, 3000, 1));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FEEDBACKRATE", "Feedback Rate", 0.1, 0.99, 0.01));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WETMIX", "Wet Mix", 0., 1., 0.01));

    return { params.begin(), params.end() };
    
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GranularSynthProjectAudioProcessor();
}

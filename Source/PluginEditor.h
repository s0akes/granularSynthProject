/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class GranularSynthProjectAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    GranularSynthProjectAudioProcessorEditor (GranularSynthProjectAudioProcessor&);
    ~GranularSynthProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GranularSynthProjectAudioProcessor& audioProcessor;

    juce::Image CAMTlogo;
    
    juce::Label randomLabel;
    juce::Label attackLabel;
    juce::Label decayLabel;
    juce::Label sussyLabel;
    juce::Label releaseLabel;
    juce::Label delayTimeLabel;
    juce::Label feedbackRateLabel;
    juce::Label wetMixLabel;
    juce::Label midiInputListLabel;
    juce::Label grainLengthLabel;
    juce::Label grainShapeLabel;
    juce::Label waveShaperLabel;


    juce::Slider randomSlider;
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sussySlider;
    juce::Slider releaseSlider;
    juce::Slider delayTime;
    juce::Slider feedbackRate;
    juce::Slider wetMix;
    juce::Slider grainLengthSlider;
    juce::Slider grainShape;
    juce::Slider waveShaper;


    //juce::ComboBox midiInputList;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decaySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sussySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> grainLengthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayTimeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackRateAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetMixAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> grainShapeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> waveShaperAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularSynthProjectAudioProcessorEditor)
};

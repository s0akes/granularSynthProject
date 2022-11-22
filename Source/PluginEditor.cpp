/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.
     TEST again icals
  ==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GranularSynthProjectAudioProcessorEditor::GranularSynthProjectAudioProcessorEditor (GranularSynthProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    setSize(735, 300); //sets size of window

    randomSlider.setRange(0.01, 10, 0.01); //creates the slider "Random"
    randomSlider.setValue(1);
    randomSlider.setSkewFactorFromMidPoint(1);
    randomSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    randomSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 95, 28);
    randomSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lightseagreen);

    attackSlider.setRange(0.01, 10, 0.01); //creates the slider "Attack"
    attackSlider.setValue(1);
    attackSlider.setSkewFactorFromMidPoint(1);
    attackSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    attackSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 95, 28);

    decaySlider.setRange(0.01, 10, 0.01); //creates the slider "Decay"
    decaySlider.setValue(1);
    decaySlider.setSkewFactorFromMidPoint(1);
    decaySlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    decaySlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 95, 28);

    sussySlider.setRange(0.01, 10, 0.01); //creates the slider "Sustain"
    sussySlider.setValue(1);
    sussySlider.setSkewFactorFromMidPoint(1);
    sussySlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    sussySlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 95, 28);

    releaseSlider.setRange(0.01, 10, 0.01); //creates the slider "Release"
    releaseSlider.setValue(1);
    releaseSlider.setSkewFactorFromMidPoint(1);
    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    releaseSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 95, 28);




    randomLabel.setFont(juce::Font(16.0f, juce::Font::bold)); //label for "Random"
    randomLabel.setText("Random", juce::dontSendNotification);
    randomLabel.setColour(juce::Label::textColourId, juce::Colours::lightseagreen);
    randomLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(&randomSlider); //makes sliders visible
    addAndMakeVisible(&attackSlider);
    addAndMakeVisible(&decaySlider);
    addAndMakeVisible(&sussySlider);
    addAndMakeVisible(&releaseSlider);
    
    addAndMakeVisible(randomLabel); //makes labels visible

    attackSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameterTree,
        "ATTACK",
        attackSlider);

    decaySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameterTree,
        "DECAY",
        decaySlider);

    sussySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameterTree,
        "SUSTAIN",
        sussySlider);

    releaseSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameterTree,
        "RELEASE",
        releaseSlider);


}

GranularSynthProjectAudioProcessorEditor::~GranularSynthProjectAudioProcessorEditor()
{
}

//==============================================================================
void GranularSynthProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

void GranularSynthProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    randomLabel.setBounds(20, 5, 95, 25);
    
    randomSlider.setBounds(20, 20, 95, 100);
    attackSlider.setBounds(170, 20, 95, 100);
    decaySlider.setBounds(320, 20, 95, 100);
    sussySlider.setBounds(470, 20, 95, 100);
    releaseSlider.setBounds(620, 20, 95, 100);
}

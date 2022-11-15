/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.
     TEST again
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


    setSize (210, 635);

    addAndMakeVisible(&randomSlider);

    randomSlider.setRange(0.01, 10, 0.01);
    randomSlider.setValue(1);
    randomSlider.setSkewFactorFromMidPoint(1);
    randomSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    randomSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 95, 28);
    randomSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lightseagreen);

}

GranularSynthProjectAudioProcessorEditor::~GranularSynthProjectAudioProcessorEditor()
{
}

//==============================================================================
void GranularSynthProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    /*g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);*/

    addAndMakeVisible(randomLabel); 
    randomLabel.setFont(juce::Font(16.0f, juce::Font::bold));
    randomLabel.setText("Random", juce::dontSendNotification);
    randomLabel.setColour(juce::Label::textColourId, juce::Colours::lightseagreen);
    randomLabel.setJustificationType(juce::Justification::centred);


}

void GranularSynthProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    randomLabel.setBounds(20, 5, 150, 25);
    randomSlider.setBounds(20, 20, 100, 100);
}

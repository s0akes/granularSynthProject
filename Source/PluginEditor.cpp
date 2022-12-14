
/*
  ==============================================================================
    This file contains the basic framework code for a JUCE plugin editor.
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

    setSize(735, 450); //sets size of window

    randomSlider.setRange(0.01, 10, 0.01); //creates the slider "Random"
    randomSlider.setValue(1);
    randomSlider.setSkewFactorFromMidPoint(1);
    randomSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    randomSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 95, 28);


    attackSlider.setRange(0.01, 10, 0.01); //creates the slider "Attack"
    attackSlider.setValue(1);
    attackSlider.setSkewFactorFromMidPoint(1);
    attackSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    attackSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 95, 28);
    attackSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lightseagreen);

    decaySlider.setRange(0.01, 10, 0.01); //creates the slider "Decay"
    decaySlider.setValue(1);
    decaySlider.setSkewFactorFromMidPoint(1);
    decaySlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    decaySlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 95, 28);
    decaySlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lightseagreen);

    sussySlider.setRange(0.01, 10, 0.01); //creates the slider "Sustain"
    sussySlider.setValue(1);
    sussySlider.setSkewFactorFromMidPoint(1);
    sussySlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    sussySlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 95, 28);
    sussySlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lightseagreen);

    releaseSlider.setRange(0.01, 10, 0.01); //creates the slider "Release"
    releaseSlider.setValue(1);
    releaseSlider.setSkewFactorFromMidPoint(1);
    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    releaseSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 95, 28);
    releaseSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lightseagreen);

    delayTime.setRange(20, 3000, 1); //creates the slider "Delay Time"
    delayTime.setValue(20);
    delayTime.setSkewFactorFromMidPoint(500);
    delayTime.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    delayTime.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 95, 28);
    delayTime.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::orange);

    feedbackRate.setRange(0.1,0.99,0.01); //creates the slider "Feedback Rate"
    feedbackRate.setValue(0.1);
    feedbackRate.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    feedbackRate.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 95, 28);
    feedbackRate.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::orange);

    wetMix.setRange(0., 1., 0.01); //creates the slider "Wet Mix"
    wetMix.setValue(0.);
    wetMix.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    wetMix.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 95, 28);
    wetMix.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::orange);

    grainLengthSlider.setRange(0., 1., 0.01); //creates the slider "Grain Size"
    grainLengthSlider.setValue(0.);
    grainLengthSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    grainLengthSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 95, 28);
    grainLengthSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::indianred);

    grainShape.setRange(0., 1., 0.01); //creates the slider "Grain Shape"
    grainShape.setValue(0.);
    grainShape.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    grainShape.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 95, 28);
    grainShape.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::indianred);

    waveShaper.setRange(1, 5, 1); //creates the slider "Wave Shape"
    waveShaper.setValue(1);
    waveShaper.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    waveShaper.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 95, 28);
    waveShaper.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::indianred);


    randomLabel.setFont(juce::Font(16.0f, juce::Font::bold)); //label for "Random"
    randomLabel.setText("Random", juce::dontSendNotification);
    randomLabel.setColour(juce::Label::textColourId, juce::Colours::lightseagreen);
    randomLabel.setJustificationType(juce::Justification::centred);

    attackLabel.setFont(juce::Font(16.0f, juce::Font::bold)); //label for "Attack"
    attackLabel.setText("Attack", juce::dontSendNotification);
    attackLabel.setColour(juce::Label::textColourId, juce::Colours::lightseagreen);
    attackLabel.setJustificationType(juce::Justification::centred);

    decayLabel.setFont(juce::Font(16.0f, juce::Font::bold)); //label for "Decay"
    decayLabel.setText("Decay", juce::dontSendNotification);
    decayLabel.setColour(juce::Label::textColourId, juce::Colours::lightseagreen);
    decayLabel.setJustificationType(juce::Justification::centred);

    sussyLabel.setFont(juce::Font(16.0f, juce::Font::bold)); //label for "Sustain"
    sussyLabel.setText("Sustain", juce::dontSendNotification);
    sussyLabel.setColour(juce::Label::textColourId, juce::Colours::lightseagreen);
    sussyLabel.setJustificationType(juce::Justification::centred);

    releaseLabel.setFont(juce::Font(16.0f, juce::Font::bold)); //label for "Release"
    releaseLabel.setText("Release", juce::dontSendNotification);
    releaseLabel.setColour(juce::Label::textColourId, juce::Colours::lightseagreen);
    releaseLabel.setJustificationType(juce::Justification::centred);

    delayTimeLabel.setFont(juce::Font(16.0f, juce::Font::bold)); //label for "Delay Time"
    delayTimeLabel.setText("Delay Time (ms)", juce::dontSendNotification);
    delayTimeLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    delayTimeLabel.setJustificationType(juce::Justification::centred);

    feedbackRateLabel.setFont(juce::Font(16.0f, juce::Font::bold)); //label for "Feedback Rate"
    feedbackRateLabel.setText("Feedback Rate", juce::dontSendNotification);
    feedbackRateLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    feedbackRateLabel.setJustificationType(juce::Justification::centred);

    wetMixLabel.setFont(juce::Font(16.0f, juce::Font::bold)); //label for "Wet Mix"
    wetMixLabel.setText("Wet Mix %", juce::dontSendNotification);
    wetMixLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    wetMixLabel.setJustificationType(juce::Justification::centred);

    grainLengthLabel.setFont(juce::Font(16.0f, juce::Font::bold)); //label for "Grain Length"
    grainLengthLabel.setText("Grain Length", juce::dontSendNotification);
    grainLengthLabel.setColour(juce::Label::textColourId, juce::Colours::indianred);
    grainLengthLabel.setJustificationType(juce::Justification::centred);

    grainShapeLabel.setFont(juce::Font(16.0f, juce::Font::bold)); //label for "Grain Shape"
    grainShapeLabel.setText("Grain Shape", juce::dontSendNotification);
    grainShapeLabel.setColour(juce::Label::textColourId, juce::Colours::indianred);
    grainShapeLabel.setJustificationType(juce::Justification::centred);

    waveShaperLabel.setFont(juce::Font(16.0f, juce::Font::bold)); //label for "Waveshaper"
    waveShaperLabel.setText("Waveshaper", juce::dontSendNotification);
    waveShaperLabel.setColour(juce::Label::textColourId, juce::Colours::indianred);
    waveShaperLabel.setJustificationType(juce::Justification::centred);


    addAndMakeVisible(&randomSlider); //makes sliders visible
    addAndMakeVisible(&attackSlider);
    addAndMakeVisible(&decaySlider);
    addAndMakeVisible(&sussySlider);
    addAndMakeVisible(&releaseSlider);
    addAndMakeVisible(&delayTime);
    addAndMakeVisible(&feedbackRate);
    addAndMakeVisible(&wetMix);
    addAndMakeVisible(&grainLengthSlider);
    addAndMakeVisible(&grainShape);
    addAndMakeVisible(&waveShaper);
    
    addAndMakeVisible(randomLabel);//makes labels visible
    addAndMakeVisible(attackLabel);
    addAndMakeVisible(decayLabel);
    addAndMakeVisible(sussyLabel);
    addAndMakeVisible(releaseLabel);
    addAndMakeVisible(delayTimeLabel);
    addAndMakeVisible(feedbackRateLabel);
    addAndMakeVisible(wetMixLabel);
    addAndMakeVisible(grainLengthLabel);
    addAndMakeVisible(grainShapeLabel);
    addAndMakeVisible(waveShaperLabel);

    /*addAndMakeVisible(midiInputListLabel);
    midiInputListLabel.setText("MIDI Input:", juce::dontSendNotification);
    midiInputListLabel.attachToComponent(&midiInputList, true);*/

    //addAndMakeVisible(midiInputList);
    //midiInputList.setTextWhenNoChoicesAvailable("No MIDI Inputs Enabled");
    //auto midiInputs = juce::MidiInput::getAvailableDevices();

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

    grainLengthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameterTree,
        "GRAINLENGTH",
        grainLengthSlider);

    delayTimeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameterTree,
        "DELAYTIME",
        delayTime);

    feedbackRateAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameterTree,
        "FEEDBACKRATE",
        feedbackRate);

    wetMixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameterTree,
        "WETMIX",
        wetMix);

    grainShapeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameterTree,
        "GRAINSHAPE",
        grainShape);

    waveShaperAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameterTree,
        "WAVESHAPER",
        waveShaper);
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
    CAMTlogo = juce::ImageCache::getFromMemory(BinaryData::logopng_png, BinaryData::logopng_pngSize);
    g.drawImageWithin(CAMTlogo, 545, 170, 200, 85, juce::RectanglePlacement::stretchToFit);
}

void GranularSynthProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getLocalBounds();
    
    //row 1
    randomLabel.setBounds(20, 5, 95, 25);
    attackLabel.setBounds(170, 5, 95, 25);
    decayLabel.setBounds(320, 5, 95, 25);
    sussyLabel.setBounds(470, 5, 95, 25);
    releaseLabel.setBounds(620, 5, 95, 25);
    //2
    grainLengthLabel.setBounds(20, 160, 95, 25);
    grainShapeLabel.setBounds(170, 160, 95, 25);
    waveShaperLabel.setBounds(320, 160, 95, 25);
    //3
    delayTimeLabel.setBounds(20, 315, 105, 25);
    feedbackRateLabel.setBounds(170, 315, 95, 25);
    wetMixLabel.setBounds(320, 315, 95, 25);
    
    //row 1
    randomSlider.setBounds(20, 20, 95, 100);
    attackSlider.setBounds(170, 20, 95, 100);
    decaySlider.setBounds(320, 20, 95, 100);
    sussySlider.setBounds(470, 20, 95, 100);
    releaseSlider.setBounds(620, 20, 95, 100);
    
    grainLengthSlider.setBounds(20, 175, 95, 100);
    grainShape.setBounds(170, 175, 95, 100);
    waveShaper.setBounds(320, 175, 95, 100);

    delayTime.setBounds(20, 330, 95, 100);
    feedbackRate.setBounds(170, 330, 95, 100);
    wetMix.setBounds(320, 330, 95, 100);

    //midiInputList.setBounds(125, 279, 570, 18);
}

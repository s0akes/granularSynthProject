/*
  ==============================================================================

    Distortion.h
    Created: 30 Mar 2022 9:34:22am
    Author:  Mace Noonan

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>

enum DistProfileIds 
    {
    CleanId = 1,
    HardClipId = 2,
    BitCrushId = 3,
    SquareId = 4,
    RectId = 5
    };

class Dist
{
public:
    Dist();

    void SetDistProfile(int profile, double gain);

    double distort(double in);

    double SoftClip(double in);

    juce::AudioSampleBuffer Waveshape;



private:

    int samples = 8192;

    void HardClip(juce::AudioSampleBuffer* in, double gain);
    void BitCrush(juce::AudioSampleBuffer* in, double gain);
    void clean(juce::AudioSampleBuffer* in, double gain);
    void Square(juce::AudioSampleBuffer* in, double gain);
    void Rect(juce::AudioSampleBuffer* in, double gain);
};
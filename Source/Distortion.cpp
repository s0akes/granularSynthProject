/*
  ==============================================================================

    Distortion.cpp
    Created: 30 Mar 2022 9:34:22am
    Author:  Mace Noonan

  ==============================================================================
*/

#include "Distortion.h"
#include <cmath>
#include <math.h>

Dist::Dist() 
{
    Waveshape.setSize(1, samples);
    Waveshape.clear();
    clean(&Waveshape, 1);

}

void Dist::SetDistProfile(int profile, double gain)
{
    if (profile == CleanId) {
        clean(&Waveshape, gain);
    }
    else if (profile == HardClipId) {
        HardClip(&Waveshape, gain);
    }
    else if (profile == BitCrushId) {
        BitCrush(&Waveshape, gain);
    }
    else if (profile == SquareId) {
        Square(&Waveshape, gain);
    }
    else if (profile == RectId) {
        Rect(&Waveshape, gain);
    }
}

double Dist::SoftClip(double in)
{
    if (in > 1) {
        in = 2/3;
    }
    else if (1 >= in >= -1) {
        in = in - ((in * in * in) / 3);
    }
    else if (in < -1) {
        in = -2/3;
    }

    return in;
}


double Dist::distort(double in)
{
    auto* data = Waveshape.getReadPointer(0);

    double samp = (in * samples);
    samp = (double)samp + samples;
    samp = (double)samp / 2;
    int low = samp;
    if (low >= samples) {
        low = samples - 1;
    }
    else if (low < 0) {
        low = 0;
    }
    int high = low + 1;
  
    double frac = (double)samp - low;
    double V;
    double V1 = data[low];
    double V2 = data[high];
    V = (frac * V2) + ((1 - frac) * V1);

    return V;
}
void Dist::clean(juce::AudioSampleBuffer* in, double gain)
{
    auto* data = in->getWritePointer(0);

    for (int i = 0; i < samples; i++)
    {
        double j = (double)i / samples;
        j = j * 2;
        j = j - 1;
        data[i] = j;
    }
}

void Dist::HardClip(juce::AudioSampleBuffer* in, double gain)
{
    auto* data = in->getWritePointer(0);

    for (int i = 0; i < samples; i++)
    {
        double j = (double)i / samples;
        j = j * 2;
        j = j - 1;
        j = j * gain;
        if (j > 1) {
            j = 1;
        }
        else if (j < -1) {
            j = -1;
        }
        data[i] = j;
    }
}

void Dist::BitCrush(juce::AudioSampleBuffer* in, double gain)
{
    auto* data = in->getWritePointer(0);

    for (int i = 0; i < samples; i++)
    {
        double j = (double)i / samples;
        j = j * 2;
        j = j - 1;
        j = j * (11-gain) * 50;
        int k = j;
        j = (double)k / (50 * (11 - gain));
        if (j == 0) {
            j = 1;
        }
        data[i] = j;
    }
}

void Dist::Square(juce::AudioSampleBuffer* in, double gain)
{
    auto* data = in->getWritePointer(0);

    for (int i = 0; i < samples; i++)
    {
        double j = (double)i / samples;
        j = j * 2;
        j = j - 1;
        double x = (double) (1 / gain);
        if (j >= 0) {
            data[i] = pow(j, x);
        }
        else {
            j = abs(j);
            j = pow(j, x);
            data[i] = 0 - j;
        }

    }
}

void Dist::Rect(juce::AudioSampleBuffer* in, double gain)
{
    for (int i = 0; i < samples; i++)
    {
        auto* data = in->getWritePointer(0);

        double j = (double)i / samples;
        j = j * 2;
        j = j - 1;
        j = abs(j);
        j = j * gain;
        if (j > 1) {
            j = 1;
        }
        j = j - 0.5;
        j = j * 2;
        data[i] = j;
    }
}

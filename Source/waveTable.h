/*
  ==============================================================================

    waveTable.h
    Created: 15 Nov 2022 3:05:14pm
    Author:  Mace Noonan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class sinSound: public juce::SynthesiserSound 
{
public:
    
    sinSound () 
    {
        int tableSize = 512;
        waveTable.setSize(1, tableSize);
        auto data = waveTable.getWritePointer(0);
        
        auto angleDelta = juce::MathConstants<double>::twoPi / (double)(tableSize);
        auto currentAngle = 0.0;
        
        for (unsigned int i = 0; i < tableSize; ++i)
        {
            auto sample = std::sin(currentAngle);
            data[i] = (float)sample;
            currentAngle += angleDelta;
        }
    }
    
    bool appliesToNote (int midiNoteNumber) override 
    {
        return true;
    }
    
    bool appliesToChannel (int midiChannel) override 
    {
        return true;
    }
    
    juce::AudioSampleBuffer waveTable;

private:

};


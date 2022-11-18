
#pragma once

#include <JuceHeader.h>

class waveTableClass: public juce::SynthesiserSound //this is the sinthesisersoud class
{
public:
    
    waveTableClass () 
    {
        int tableSize = 512;
        waveTable.setSize(1, tableSize);
        auto data = waveTable.getWritePointer(0);
        
        auto angleDelta = juce::MathConstants<double>::twoPi / (double)(tableSize); //coppied this lol
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


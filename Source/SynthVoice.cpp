/*
  ==============================================================================

    SynthVoice.cpp
    Created: 15 Nov 2022 4:00:12pm
    Author:  (s) Daniel G Jones

  ==============================================================================
*/

#include "SynthVoice.h"

synthVoice::synthVoice(double frequency, int amplitude, double duration){
  //take the noteon() and noteoff() data and send the respective amplitude, frequency and duration data on to the graining class
  void  synthVoice (double freq, int ampl, double time){

  }

  bool  canPlaySound (juce::SynthesiserSound * sound){

      return (dynamic_cast<waveTableClass*>(sound) != nullptr) ;
      
  }
    
  void  startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition){

    WT = &(dynamic_cast<sinSound*>(sound) -> waveTable);
    
    auto f = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    delta = WT->getNumSamples() * f / getSampleRate();
    
    amplitude = velocity * 0.2;
     
    currentIndex = 0;

  }
    
  void  stopNote (float velocity, bool allowTailOff){

    amplitude = 0.0;
    clearCurrentNote();

  }
    
  void  renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples){

     if (!isVoiceActive() || waveTableClass == nullptr){

        return;

     }  
    
    for (int i = startSample; i<numSamples+startSample; i++){
        
        double vel;

        int tableSize = WT->getNumSamples();

        int index0 = (int) currentIndex;
        int index1;
        if (index0 == tablesize - 1){
          index1 = 0;
        } else {
          index1 = index0 + 1
        }

        double frac = currentIndex - (double) index0;
        double vel0 = WT->getSample(0, index0);
        double vel1 = WT->getSample(0, index1);
        vel = frac * vel1 + (1 - frac) * vel0;

        vel *= ampl;

        currentIndex += delta;
        if (currentIndex >= (double)tableSize){
          currentIndex -= tableSize;
        }

        for(int j = 0; j < outputBuffer.getNumChannels(); j++){
          outputBuffer.addSample(j, i, vel);
        }

    }

  }

}


//randomly trigger a grain store the grain in a vector
//every sample check grain::isActive() 
//if it is acitve grain::getNextSample
//if it is not active then delete the grain
//repeat for every grain in the vector
//add the samples together
//output to buffer
//done :)
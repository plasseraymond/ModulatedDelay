/*
  ==============================================================================

    ModulatedDelayEffect.h
    Created: 29 Mar 2024 9:39:10pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#pragma once
#include "LFO.h"

class ModulatedDelayEffect {
public:
    // virtual dtor for derived classes
    virtual ~ModulatedDelayEffect() {
        // empty block
    }
    
    // virtual prepare method for derived classes
    virtual void prepare(double sampleRate) {
        Fs = sampleRate;
        lfo.prepare(sampleRate); // calls LFO's prepare method
    }
    
    // generic process method for each AudioBuffer
    void process(float * buffer, const int N, const int c);
    
    // PURE virtual processSample method which each derived class MUST override
    virtual float processSample(float x, const int c, float lfoValue) = 0;
    
    // mutators for rate, depth, delay, and wet parameters
    void setRate(float rate) {
        this->rate = rate;
    }
    
    void setDepth(float depth) {
        this->depth = depth;
    }
    
    void setDelay(float delay) {
        this->delay = delay;
    }
    
    void setWet(float wet) {
        this->wet = (wet / 100.f);
    }
    
protected:
    // at one point in time Fs had to be under protected access specifier, not sure if that still holds
    double Fs = 1.0;
    
private:
    float rate = 0.1f;
    float depth = 1.f;
    float delay = 1.f;
    float wet = 0.f;
    
    // LFO object as private data member
    LFO lfo;
};

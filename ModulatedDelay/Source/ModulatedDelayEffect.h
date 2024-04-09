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
    virtual ~ModulatedDelayEffect() {
        // empty block
    }
    
    virtual void prepare(double sampleRate) {
        Fs = sampleRate;
        lfo.prepare(sampleRate);
    }
    
    void process(float * buffer, const int N, const int c);
    
    virtual float processSample(float x, const int c, float lfoValue) = 0;
    
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
    double Fs = 1.0;
    
private:
    float rate = 0.6f;
    float depth = 5.f;
    float delay = 30.f;
    float wet = 0.5f;
    
    LFO lfo;
};

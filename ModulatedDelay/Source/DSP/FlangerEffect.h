/*
  ==============================================================================

    FlangerEffect.h
    Created: 9 Apr 2024 10:19:57pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#pragma once
#include "ModulatedDelayEffect.h"
#include "FractionalDelay.h"

class FlangerEffect : public ModulatedDelayEffect {
public:
    // override of base class's prepare method which actually utilizes base class's prepare implementation
    void prepare(double sampleRate) override {
        ModulatedDelayEffect::prepare(sampleRate);
        fd.prepare(sampleRate); // prepares FractionalDelay object data member unique to FlangerEffect
    }
    
    // override of base class's processSample method (REQUIRED)
    float processSample(float x, const int c, float lfoValue) override;

private:
    // FractionalDelay object as private data member
    FractionalDelay fd;
};

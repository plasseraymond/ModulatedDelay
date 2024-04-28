/*
  ==============================================================================

    PhaserEffect.h
    Created: 10 Apr 2024 11:13:44pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#pragma once
#include "ModulatedDelayEffect.h"
#include "Biquad.h"

class PhaserEffect : public ModulatedDelayEffect {
public:
    // override of base class's prepare method which actually utilizes base class's prepare implementation
    void prepare(double sampleRate) override {
        ModulatedDelayEffect::prepare(sampleRate);
        bq.prepare(sampleRate); // prepares Biquad object data member unique to PhaserEffect
    }
    
    // override of base class's processSample method (REQUIRED)
    float processSample(float x, const int c, float lfoValue) override;

private:
    // Biquad object as private data member
    Biquad bq;
};

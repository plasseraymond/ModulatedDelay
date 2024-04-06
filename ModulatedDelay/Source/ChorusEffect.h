/*
  ==============================================================================

    ChorusEffect.h
    Created: 29 Mar 2024 9:31:09pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#pragma once
#include "ModulatedDelayEffect.h"
#include "FractionalDelay.h"

class ChorusEffect : public ModulatedDelayEffect {
public:
    void prepare(double sampleRate) override {
        ModulatedDelayEffect::prepare(sampleRate);
        fd.prepare(sampleRate);
    }
    
    float processSample(float x, const int c, float lfoValue) override;

private:
    FractionalDelay fd;
};

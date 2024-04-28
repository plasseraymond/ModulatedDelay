/*
  ==============================================================================

    FlangerEffect.cpp
    Created: 9 Apr 2024 10:19:57pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#include "FlangerEffect.h"

float FlangerEffect::processSample(float x, const int c, float lfoValue) {
    // convert lfoValue to be in samples instead of ms
    lfoValue = lfoValue * 1000.f / Fs;
    
    // call FractionalDelay's processDelay method to compute the appropriate delay for the effect
    return fd.processDelay(x, c, lfoValue);
}

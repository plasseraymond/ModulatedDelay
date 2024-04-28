/*
  ==============================================================================

    PhaserEffect.cpp
    Created: 10 Apr 2024 11:13:44pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#include "PhaserEffect.h"

float PhaserEffect::processSample(float x, const int c, float lfoValue) {
    // call Biquad's processDelay method to compute the appropriate delay for the effect
    return bq.processDelay(x, c, lfoValue);
}

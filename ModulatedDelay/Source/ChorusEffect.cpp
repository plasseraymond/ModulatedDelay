/*
  ==============================================================================

    ChorusEffect.cpp
    Created: 29 Mar 2024 9:31:09pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#include "ChorusEffect.h"

float ChorusEffect::processSample(float x, const int c, float lfoValue) {
    return fd.processDelay(x, c, lfoValue);
}

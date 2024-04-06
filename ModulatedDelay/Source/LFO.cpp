/*
  ==============================================================================

    LFO.cpp
    Created: 29 Mar 2024 9:32:35pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#include "LFO.h"

float LFO::calculate(float rate, float depth, float delay) {
    float angleChange = rate * (1.f/Fs) * 2.f * M_PI;
    float lfoValue = depth * sin(currentAngle) + delay;
    
    currentAngle += angleChange;
    
    if(currentAngle > 2.f * M_PI) {
        currentAngle -= 2.f * M_PI;
    }
    
    return lfoValue;
}

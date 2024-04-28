/*
  ==============================================================================

    LFO.cpp
    Created: 29 Mar 2024 9:32:35pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#include "LFO.h"

float LFO::calculate(float rate, float depth, float delay, const int c) {
    
    smoothedDepth[c] = alpha * smoothedDepth[c] + (1.f - alpha) * depth;
    smoothedDelay[c] = alpha * smoothedDelay[c] + (1.f - alpha) * delay;
    
    // determine the angle by which the LFO traverses the unit circle
    float angleChange = rate * (1.f/Fs) * 2.f * M_PI;
    
    // calculate the LFO's value at its current angle
    float lfoValue = smoothedDepth[c] * sin(currentAngle[c]) + smoothedDelay[c];
    
    // update the current angle based on the angle of change
    currentAngle[c] += angleChange;
    
    // check for when the current angle exceeds 2*pi
    if(currentAngle[c] > 2.f * M_PI) {
        currentAngle[c] = 0.f;
    }
    
    return lfoValue;
}

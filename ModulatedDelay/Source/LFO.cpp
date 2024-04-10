/*
  ==============================================================================

    LFO.cpp
    Created: 29 Mar 2024 9:32:35pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#include "LFO.h"

float LFO::calculate(float rate, float depth, float delay) {
    // determine the angle by which the LFO traverses the unit circle
    float angleChange = rate * (1.f/Fs) * 2.f * M_PI;
    
    // calculate the LFO's value at its current angle
    float lfoValue = depth * sin(currentAngle) + delay;
    
    // update the current angle based on the angle of change
    currentAngle += angleChange;
    
    // check for when the current angle exceeds 2*pi
    if(currentAngle > 2.f * M_PI) {
        currentAngle = 0.f;
    }
    
    return lfoValue;
}

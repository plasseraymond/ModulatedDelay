/*
  ==============================================================================

    Biquad.cpp
    Created: 10 Apr 2024 11:14:03pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#include "Biquad.h"

float Biquad::processDelay(float x, const int c, float lfoValue) {
    // determine normalized frequency value based on LFO
    w0 = (float)(2.f * M_PI * lfoValue / Fs);
    
    // determine alpha
    alpha = std::sin(w0) / (2.f * 0.5f);

    // use APF implementation to update coefficients based on Audio EQ Cookbook
    updateCoefficients();
    
    // determine output
    float y = (b0 / a0) * x + (b1 / a0) * x1[c] + (b2 / a0) * x2[c]
            + (-a1 / a0) * y1[c] + (-a2 / a0) * y2[c];

    // store delay samples for next process step
    x2[c] = x1[c];
    x1[c] = x;
    y2[c] = y1[c];
    y1[c] = y;

    return y;
}

void Biquad::updateCoefficients() {
    // APF recipe
    b0 = 1.f - alpha;
    b1 = -2.f * std::cos(w0);
    b2 = 1.f + alpha;
    a0 = 1.f + alpha;
    a1 = -2.f * std::cos(w0);
    a2 = 1.f - alpha;
}

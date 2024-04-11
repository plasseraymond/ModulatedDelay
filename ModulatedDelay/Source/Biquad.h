/*
  ==============================================================================

    Biquad.h
    Created: 10 Apr 2024 11:14:03pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#pragma once

#include <cmath>

class Biquad {
public:
    // unique prepare method to assign Fs & update coefficients
    void prepare(double Fs) {
        this->Fs = float(Fs);
        updateCoefficients();
    }
    
    // processDelay method for calculating biquad delay given the LFO's value & Q value
    float processDelay(float x, const int c, float lfoValue);

private:
    float Fs = 1.f;

    // intermediate variables
    float w0 = 0.f;
    float alpha = 0.f;

    // variables for Biquad implementation: 2 channels, up to 2nd order
    float x1[2] = { 0.0f }; // 1 sample of delay feedforward
    float x2[2] = { 0.0f }; // 2 samples of delay feedforward
    float y1[2] = { 0.0f }; // 1 sample of delay feedback
    float y2[2] = { 0.0f }; // 2 samples of delay feedback

    // filter coefficients
    float b0 = 1.0f;
    float b1 = 0.0f;
    float b2 = 0.0f;
    float a0 = 1.0f;
    float a1 = 0.0f;
    float a2 = 0.0f;

    void updateCoefficients();
};

/*
  ==============================================================================

    LFO.h
    Created: 29 Mar 2024 9:32:35pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#pragma once
#include <cmath>

class LFO {
public:
    // unique prepare method to assign Fs
    void prepare(double Fs) {
        this->Fs = float(Fs);
        alpha = std::exp(-std::log(9.f)/(Fs * respTime));
    }
    
    // calculate method for determining LFO's value given the three common params
    float calculate(float rate, float depth, float delay, const int c);
    
private:
    float Fs = 1.f;
    
    // keeps track of position along unit circle for L & R channels
    float currentAngle[2] = {0.f};
    
    // smoothing parameters
    float smoothedRate[2] = {0.f};
    float smoothedDepth[2] = {0.f};
    float smoothedDelay[2] = {0.f};
    float alpha = 0.999f;
    const float respTime = 0.1f;
};

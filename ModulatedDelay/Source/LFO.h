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
    void prepare(double Fs) {
        this->Fs = float(Fs);
    }
    
    float calculate(float rate, float depth, float delay);
    
private:
    float Fs = 1.f;
    float currentAngle = 0.f;
};

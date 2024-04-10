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
    }
    
    // calculate method for determining LFO's value given the three common params
    float calculate(float rate, float depth, float delay);
    
private:
    float Fs = 1.f;
    float currentAngle = 0.f; // keeps track of position along unit circle
};

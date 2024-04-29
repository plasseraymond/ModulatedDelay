/*
  ==============================================================================

    FractionalDelay.h
    Created: 29 Mar 2024 9:31:41pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#pragma once
#include <iostream>

class FractionalDelay {
public:
    // unique prepare method to assign Fs
    void prepare(double Fs) {
        this->Fs = float(Fs);
    }
    
    // processDelay method for calculating fractional delay given the LFO's value
    float processDelay(float x, const int c, float lfoValue);
    
private:
    float Fs = 1.f;
    
    // delay buffer information
    const int MAX_BUFFER_SIZE = 96000;
    float delayBuffer[96000][2] = {0.f};
    int index[2] = {0};
};

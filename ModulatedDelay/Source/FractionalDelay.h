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
    void prepare(double Fs) {
        this->Fs = float(Fs);
    }
    
    float processDelay(float x, const int c, float lfoValue);
    
private:
    float Fs = 1.f;
    
    const int MAX_BUFFER_SIZE = 96000;
    float delayBuffer[96000][2] = {0.f};
    int index[2] = {0};
};

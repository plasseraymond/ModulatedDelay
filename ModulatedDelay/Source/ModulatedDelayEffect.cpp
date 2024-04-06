/*
  ==============================================================================

    ModulatedDelayEffect.cpp
    Created: 29 Mar 2024 9:39:10pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#include "ModulatedDelayEffect.h"

void ModulatedDelayEffect::process(float * buffer, const int N, const int c) {
    
    for(int n = 0; n < N; ++n) {
        float lfoValue = lfo.calculate(rate, depth, delay);
        
        float x = buffer[n];
        float y = processSample(x, c, lfoValue);
        
        float out = (1.f - wet) * x + wet * y;
        buffer[n] = out;
    }
}

/*
  ==============================================================================

    ModulatedDelayEffect.cpp
    Created: 29 Mar 2024 9:39:10pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#include "ModulatedDelayEffect.h"

void ModulatedDelayEffect::process(float * buffer, const int N, const int c) {
    
    // loop through all samples in buffer
    for(int n = 0; n < N; ++n) {
        // first get the value of the LFO given the current state of rate, depth, and delay
        float lfoValue = lfo.calculate(rate, depth, delay, c);
        
        // next process the input signal using the determined LFO value
        float x = buffer[n];
        float y = processSample(x, c, lfoValue);
        
        // finally combine the wet and dry paths and overwrite the input
        float out = (1.f - wet) * x + wet * y;
        buffer[n] = out;
    }
}

/*
  ==============================================================================

    FractionalDelay.cpp
    Created: 29 Mar 2024 9:31:41pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#include "FractionalDelay.h"

float FractionalDelay::processDelay(float x, const int c, float lfoValue) {
    // convert LFO value into samples
    float lfoSamples = (lfoValue / 1000.f) * Fs;

    // determine (fractional) delay
    int d1 = floor(lfoSamples);
    int d2 = d1 + 1;
    float g2 = lfoSamples - (float)d1;
    float g1 = 1.f - g2;

    // determine indexes given delay time
    int indexD1 = index[c] - d1;
    if(indexD1 < 0) {
        indexD1 += MAX_BUFFER_SIZE;
    }

    int indexD2 = index[c] - d2;
    if(indexD2 < 0) {
        indexD2 += MAX_BUFFER_SIZE;
    }

    // interpolate output (linear)
    float y = g1 * delayBuffer[indexD1][c] + g2 * delayBuffer[indexD2][c];

    // prepare delay buffer
    delayBuffer[index[c]][c] = x;
    if(index[c] < MAX_BUFFER_SIZE - 1) {
        index[c]++;
    }
    else {
        index[c] = 0;
    }

    return y;
}

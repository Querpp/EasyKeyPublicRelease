#ifndef PHASER_H
#define PHASER_H

#include "GlobalVariables.h"

struct AllpassFilter {
    vector<float> buf;
    size_t idx = 0;       // Write index
    float apFeedback = 0.5f;
    float delay = 1.0f;   // Dynamic delay in samples (can be fractional)
};

struct Phaser {
    int numStages;
    int fs;
    float lfoPhase;
    float lfoInc;
    float feedback;
    size_t baseDelaySamples;
    size_t depthSamples;
    vector<AllpassFilter> allpasses;
};

// Setup functions
void initPhaser(Phaser& ph, int stages, float lfoHz, float depthMs, float baseDelayMs, float feedback);
void setAllpassDelay(AllpassFilter& ap, size_t n);

// Processing functions
float processPhaserSample(Phaser& ph, float in);
float processAllpassSample(AllpassFilter& ap, float x);

// Effect processor
void PhaserEffect(int PhsRate, int PhsMix);

#endif // PHASER_H

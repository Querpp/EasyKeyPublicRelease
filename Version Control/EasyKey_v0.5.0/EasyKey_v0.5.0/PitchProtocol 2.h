#ifndef PITCHPROTOCOL_H
#define PITCHPROTOCOL_H

#include "GlobalVariables.h"

// We want 13 keys centered on A3 (220 Hz, MIDI note 57).
// This example uses MIDI note numbers 51 to 63 (inclusive).
const int numPitchFrequencies = 18;
const double pitchFrequencies[numPitchFrequencies] = {
    130.81,
    138.59,
    146.83,
    155.56,
    164.81,
    174.61,
    185.00,
    196.00,
    207.65,
    220.00,
    233.08,
    246.94,
    261.63,
    277.18,
    293.66,
    311.13,
    329.63,
    349.23
};

// Initialize with a default index (e.g., 0 for C4)
int selectedPitchIndex = 0;


#endif //PITCHPROTOCOL_H

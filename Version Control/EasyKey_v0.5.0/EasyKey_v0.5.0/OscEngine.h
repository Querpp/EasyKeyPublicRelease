#ifndef OSC_ENGINE_H
#define OSC_ENGINE_H

#include "GlobalVariables.h"

// Global variable for the selected waveform type
extern WaveType selectedWaveform;

// Maps the waveform type to its corresponding lookup table file name.
vector<double> getLookupTable(WaveType type);

// Declaration of the main engine function
void OscEngine(WaveType chosenWave);

// Writes a vector of 16-bit samples to a WAV file with the given sample rate.
void writeWavFile(const string &filename, const vector<int16_t> &samples);

#endif // OSC_ENGINE_H

#include "Filter.h"
#include "OscEngine.h"

#include "SAW.h"
#include "SQUARE.h"
#include "SINE.h"
#include "GLORKGLUNK.h"
#include "DRUMFILL.h"
#include "DUNE.h"

// Soft clipping distortion function.
// Multiplies the input by drive and then applies a soft clip:
// y = (x * drive) / (1 + |x * drive|)
double softClip(double x, double drive) {
    x *= drive;
    return x / (1.0 + fabs(x));
}

// Replaces the original lowpass filter with a distortion process.
void LowpassFilter(int fc, int order)
{
    // 1. Set chosen vectorTable:
    // Retrieve the pre-generated lookup table for the current waveform.
    vector<double> selectedWaveform = getLookupTable(currentWaveType);

    // Get the number of points in the lookup table.
    unsigned long N = selectedWaveform.size();

    // Create a new vector to hold the distorted signal.
    vector<double> distortedSignal(N, 0.0);

    // 2. Apply Distortion:
    // Define a drive value to control distortion intensity.
    double drive = 3.0;
    for (int i = 0; i < N; i++) {
        // Process each sample with soft clipping.
        distortedSignal[i] = softClip(selectedWaveform[i], drive);
    }

    // 3. Normalize the Distorted Signal to [-1, 1]:
    double maxVal = 0.0;
    for (int i = 0; i < N; i++) {
        if (fabs(distortedSignal[i]) > maxVal)
            maxVal = fabs(distortedSignal[i]);
    }
    if (maxVal > 0) {
        for (int i = 0; i < N; i++) {
            distortedSignal[i] /= maxVal;
        }
    }

    // 4. Set global vector to processed signal and update the waveform type
    filteredTable = distortedSignal;
    currentWaveType = WaveType::FILTERED;

    // 5. Process the distorted signal (generate output WAV, etc.)
    OscEngine(WaveType::FILTERED);
}

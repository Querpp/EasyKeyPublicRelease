#include "Distortion.h"
#include "OscEngine.h"

#include "SAW.h"
#include "SQUARE.h"
#include "SINE.h"
#include "GLORKGLUNK.h"
#include "DRUMFILL.h"
#include "DUNE.h"


// DistortionSelection
double distortionSelection(int algorithm, int drive, double x, double threshold) {
    switch (algorithm) {
            // Soft Clip
        case 1:
            x *= drive;
            return x / (1.0 + fabs(x));
            
            // Foldback
        case 2:
            x *= drive;
            if (x > threshold || x < -threshold) {
                x = fabs(fabs(fmod(x - threshold, threshold * 4.0)) - threshold * 2.0) - threshold;
            }
            return x;
            break;
            
            // Default: passthrough
        default:
            return x;
            break;
    }
}


void DistortionEffect(int DistAlg, int DistDrive)
{
    // Get original waveform
    vector<double> selectedWaveform = getLookupTable(currentWaveType);
    size_t tableSize = selectedWaveform.size();
    vector<double> distortedTable(tableSize, 0.0);
    
    const int numSamples = SampleRate * DurationSeconds;
    const double frequency = 100.0;
    const double phaseIncrement = (tableSize * frequency) / SampleRate;
    const double threshold = 0.8; // Can be parameterized if needed
    
    // Apply distortion
    for (size_t i = 0; i < tableSize; ++i) {
        distortedTable[i] = distortionSelection(DistAlg, DistDrive, selectedWaveform[i], threshold);
    }
    
    // Normalize to [-1.0, 1.0]
    double maxVal = 0.0;
    for (double val : distortedTable) {
        maxVal = max(maxVal, fabs(val));
    }
    if (maxVal > 0.0) {
        for (double& val : distortedTable) {
            val /= maxVal;
        }
    }
    
    // Convert to audio samples
    vector<int16_t> distortedSamples;
    distortedSamples.reserve(numSamples);
    double phase = 0.0;
    for (int i = 0; i < numSamples; ++i) {
        int index = static_cast<int>(phase) % tableSize;
        double value = distortedTable[index];
        distortedSamples.push_back(static_cast<int16_t>(Amplitude * value));
        phase += phaseIncrement;
        if (phase >= tableSize) phase -= tableSize;
    }
    
    // Update global state
    processedTable = distortedTable;
    currentWaveType = WaveType::PROCESSED;
    
    // Send to playback engine
    OscEngine(WaveType::PROCESSED);
}

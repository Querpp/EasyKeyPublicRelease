#include "AudioFormats.h"
#include "OscEngine.h"
#include "Paths.h"
#include "PitchProtocol.h"

#include "SAW.h"
#include "SINE.h"
#include "SQUARE.h"
#include "GLORKGLUNK.h"
#include "DRUMFILL.h"
#include "DUNE.h"


// Maps the waveform type to its corresponding lookup table file name.
vector<double> getLookupTable(WaveType type)
{
    switch (type)
    {
        case WaveType::SAW:         return sawTable;
        case WaveType::SQUARE:      return squareTable;
        case WaveType::SINE:        return sineTable;
        case WaveType::GLORKGLUNK:  return glorkglunkTable;
        case WaveType::DRUMFILL:    return drumfillTable;
        case WaveType::DUNE:        return duneTable;
        case WaveType::PROCESSED:   return processedTable;
        default:                    return chosenTable;
    }
}


// Generates waveform
void OscEngine(WaveType chosenWave)
{
    // --- Lookup Table Loading ---
    // Get the lookup table file name and load it.
    vector<double> currWaveTable = getLookupTable(chosenWave);
    unsigned long tableSize = currWaveTable.size();
    
    // --- Audio Generation Parameters ---
    const int numSamples = SampleRate * DurationSeconds;            // Number of samples based on length
    const float amplitude = 0.8f;                                   // Amplitude (scale factor, in [-1,1] domain)
    
    // Loop over the frequencies and generate a WAV file for each pitch
    for (int i = 0; i < numPitchFrequencies; i++)
    {
        // --- Generate Audio Samples ---
        // Create a vector to hold 16-bit PCM samples.
        vector<int16_t> samples;
        samples.reserve(numSamples);
        
        double phase = 0.0;
        double phaseIncrement = (tableSize * pitchFrequencies[i]) / SampleRate;
        
        // Generate audio samples using a wavetable synthesis approach
        for (int j = 0; j < numSamples; j++) {
            int index = static_cast<int>(phase) % tableSize;
            
            // Retrieve the waveform value from the wavetable (normalized to [-1, 1]),
            // scale it by the amplitude, and then convert it to a 16-bit integer range.
            float normalizedSample = currWaveTable[index] * amplitude;
            int16_t sample = static_cast<int16_t>(normalizedSample * 32767);
            
            samples.push_back(sample);                      // Store the generated sample in the buffer
            phase += phaseIncrement;                        // Increment the phase to step through the wavetable
            if (phase >= tableSize) phase -= tableSize;     // Wrap the phase around if it exceeds the table size to maintain continuity
        }
        
        // --- Write Samples to WAV File ---
        string filename = "OscillatorWaveform_" + to_string(i) + ".wav";
        string filepath = getBasePath() + filename;
        writeWavFile(filepath, samples);
    }
}


// Writes a vector of 16-bit samples to a WAV file with the given sample rate.
void writeWavFile(const string &filepath, const vector<int16_t> &samples) {
    ofstream file(filepath, ios::binary);
    if (!file) {
        cerr << "Error: Cannot create file " << filepath << endl;
        return;
    }
    
    WavHeader header;
    header.sampleRate = SampleRate;
    header.byteRate = SampleRate * header.numChannels * header.bitsPerSample / 8;
    header.blockAlign = header.numChannels * header.bitsPerSample / 8;
    header.dataSize = static_cast<uint32_t>(samples.size() * sizeof(int16_t));
    header.fileSize = 36 + header.dataSize;
    
    file.write(reinterpret_cast<const char*>(&header), sizeof(WavHeader));
    file.write(reinterpret_cast<const char*>(samples.data()), header.dataSize);
    file.close();
}

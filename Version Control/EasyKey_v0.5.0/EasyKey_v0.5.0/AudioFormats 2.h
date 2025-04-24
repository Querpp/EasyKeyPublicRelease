#ifndef AUDIOFORMATS_H
#define AUDIOFORMATS_H

#include "GlobalVariables.h"

// OSCILLATOR ENGINE WAVEFORMS
// WAV file header structure for 16-bit PCM, mono audio.
struct WavHeader {
    char riff[4] = {'R','I','F','F'};
    uint32_t fileSize; // 36 + dataSize
    char wave[4] = {'W','A','V','E'};
    char fmt[4]  = {'f','m','t',' '};
    uint32_t fmtChunkSize = 16;
    uint16_t audioFormat  = 1;      // PCM
    uint16_t numChannels  = 1;      // Mono
    uint32_t sampleRate;
    uint32_t byteRate;              // sampleRate * numChannels * bitsPerSample/8
    uint16_t blockAlign;            // numChannels * bitsPerSample/8
    uint16_t bitsPerSample = 16;
    char data[4] = {'d','a','t','a'};
    uint32_t dataSize;              // numSamples * numChannels * bitsPerSample/8
};

#endif // AUDIOFORMATS_H


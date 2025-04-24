#include "Phaser.h"
#include "OscEngine.h"

#include "SAW.h"
#include "SQUARE.h"
#include "SINE.h"
#include "GLORKGLUNK.h"
#include "DRUMFILL.h"
#include "DUNE.h"


// Initializes an all-pass filter with a buffer size of `n` samples
void setAllpassDelay(AllpassFilter& ap, size_t maxSamples)
{
    ap.buf.assign(maxSamples > 0 ? maxSamples : 1, 0.0f);
    ap.idx = 0;
    ap.apFeedback = 0.5f;
}


// Processes a single sample through an all-pass filter
float processAllpassSample(AllpassFilter& ap, float x)
{
    size_t bufSize = ap.buf.size();
    
    // Calculate fractional read index based on current write index and delay
    float readIdx = float(ap.idx) - ap.delay;
    if (readIdx < 0) readIdx += bufSize;
    
    // Integer and fractional parts
    size_t idx0 = size_t(readIdx) % bufSize;
    size_t idx1 = (idx0 + 1) % bufSize;
    float frac = readIdx - float(idx0);
    
    // Linear interpolation
    float d = (1.0f - frac) * ap.buf[idx0] + frac * ap.buf[idx1];
    
    // All-pass difference equation
    float y = -x + d;
    ap.buf[ap.idx] = x + y * ap.apFeedback;
    
    // Advance write index
    if (++ap.idx >= bufSize) ap.idx = 0;
    
    return y;
}


// Initializes phaser parameters and internal all-pass filters
void initPhaser(Phaser& ph, int stages, float lfoHz, float depthMs, float baseDelayMs, float feedback)
{
    ph.numStages = stages;
    ph.fs = SampleRate;
    ph.lfoPhase = 0.0f;
    ph.feedback = feedback;
    ph.lfoInc = 2 * M_PI * lfoHz / float(SampleRate);
    ph.baseDelaySamples = size_t((baseDelayMs / 1000.0f) * SampleRate);
    ph.depthSamples     = size_t((depthMs    / 1000.0f) * SampleRate);
    
    size_t maxDelay = ph.baseDelaySamples + ph.depthSamples;
    
    ph.allpasses.resize(stages);
    for (auto& ap : ph.allpasses)
        setAllpassDelay(ap, maxDelay); // One-time allocation
}

float processPhaserSample(Phaser& ph, float in)
{
    // Update LFO phase
    ph.lfoPhase += ph.lfoInc;
    if (ph.lfoPhase > 2 * M_PI) ph.lfoPhase -= 2 * M_PI;
    
    // LFO modulation (0–1)
    float m = (sin(ph.lfoPhase) * 0.5f + 0.5f) * ph.depthSamples;
    float currentDelay = float(ph.baseDelaySamples) + m;
    
    // Set dynamic delay per allpass stage
    for (auto& ap : ph.allpasses)
        ap.delay = currentDelay;
    
    // Apply all-pass stages
    float out = in;
    for (auto& ap : ph.allpasses)
        out = processAllpassSample(ap, out);
    
    // Mix dry/wet
    return out * ph.feedback + in * (1.0f - ph.feedback);
}


// Main function that applies the phaser effect to an entire audio buffer
void PhaserEffect(int PhsRate, int PhsMix)
{
    // for now
    PhsRate = 100;
    PhsMix = 100;
    
    // Get original waveform
    vector<double> selectedWaveform = getLookupTable(currentWaveType);
    const unsigned long tableSize = selectedWaveform.size();
    
    const int numSamples     = SampleRate * DurationSeconds;
    const double toneFreqHz  = 100.0;
    
    vector<int16_t> original(numSamples);
    double phase = 0.0;
    double phaseInc = tableSize * toneFreqHz / SampleRate;
    
    // Proportional mapping: scale from 1-20 to 0.2-1.0 for LFO frequency
    float mappedPhsRate = 0.2f + (PhsRate - 1) * (1.0f - 0.2f) / 19.0f;
    
    // Generate original waveform into `original`
    for (int i = 0; i < numSamples; ++i) {
        int idx = int(phase) % selectedWaveform.size();
        original[i] = int16_t(Amplitude * selectedWaveform[idx]);
        phase += phaseInc;
        if (phase >= tableSize) phase -= tableSize;
    }
    
    // Set up phaser with desired parameters, including the mapped LFO rate
    Phaser ph;
    initPhaser(ph, 4, mappedPhsRate, 50.0f, 3.0f, 0.9f); // 4-stage, mapped LFO rate, 50 ms depth, 3 ms base, 90% feedback
    vector<int16_t> phasedSignal(numSamples);
    
    // Apply phaser effect sample-by-sample
    phase = 0.0;
    for (int i = 0; i < numSamples; ++i) {
        int idx = int(phase) % tableSize;
        float sampleIn = selectedWaveform[idx];
        float sampleOut = processPhaserSample(ph, sampleIn);
        
        // Apply dry/wet mix using PhsMix (0 = fully dry, 100 = fully wet)
        float mixedSample = (1.0f - PhsMix / 100.0f) * sampleIn + (PhsMix / 100.0f) * sampleOut;
        phasedSignal[i] = int16_t(mixedSample * Amplitude);
        
        phase += phaseInc;
        if (phase >= tableSize) phase -= tableSize;
    }
    
    // Normalize to prevent clipping
    int16_t maxAbs = *max_element(phasedSignal.begin(), phasedSignal.end(), [](int16_t a, int16_t b) {
        return abs(a) < abs(b);
    });
    if (maxAbs == 0) maxAbs = 1;
    
    for (int n = 0; n < numSamples; ++n)
        phasedSignal[n] = int16_t((float)phasedSignal[n] / maxAbs * Amplitude);
    
    // Convert 16-bit int samples to normalized floats for further processing/playback
    vector<double> converted(phasedSignal.size());
    for (size_t i = 0; i < phasedSignal.size(); ++i)
        converted[i] = phasedSignal[i] / Amplitude;
    
    // Store processed waveform and trigger playback/rendering
    processedTable = converted;
    currentWaveType = WaveType::PROCESSED;
    OscEngine(WaveType::PROCESSED);
}

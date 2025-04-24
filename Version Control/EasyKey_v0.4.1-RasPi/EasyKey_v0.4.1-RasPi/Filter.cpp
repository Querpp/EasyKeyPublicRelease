#include "Filter.h"
#include "OscEngine.h"

#include "SAW.h"
#include "SQUARE.h"
#include "SINE.h"
#include "GLORKGLUNK.h"
#include "DRUMFILL.h"
#include "DUNE.h"


// Lowpass Filter with variable fc and slope
double lowPassXdbPerOctave(double freq, double fc, double order)
{
    double magnitude = 1.0 / (1.0 + pow(freq / fc, order));
    return magnitude;
}

// Butterworth Lowpass Filter
double butterworthLowPass(double f, double fc, int order)
{
    // H(f) = 1 / (1 + (f/fc)^2n)
    return 1.0 / (1.0 + pow(f / fc, 2 * order));
}


void LowpassFilter(int fc, int order)
{
    // 1. Set chosen vectorTable
    vector<double> selectedWaveform = getLookupTable(currentWaveType);
    
    // Initialize vectors and values for computation
    unsigned long N = selectedWaveform.size();
    vector<double> Re(N, 0.0);      // Real part
    vector<double> Im(N, 0.0);      // Imaginary part
    vector<double> Xmag(N, 0.0);    // Magnitude
    vector<double> Xphase(N, 0.0);  // Phase
    
    // 2. COMPUTE DFT (Discrete Fourier Transform)
    for (int k = 0; k < N; k++) {
        double realPart = 0.0;
        double imagPart = 0.0;
        
        for (int n = 0; n < N; n++) {
            // Calculate the complex exponential term
            double angle = 2 * M_PI * k * n / N;  // 2π * k * n / N (frequency bin)
            realPart += selectedWaveform[n] * cos(angle);  // Real part: wavetable[n] * cos(angle)
            imagPart += selectedWaveform[n] * sin(angle);  // Imaginary part: wavetable[n] * sin(angle)
        }
        // Store the real and imaginary parts
        Re[k] = realPart;
        Im[k] = imagPart;
    }
    // Magnitude + Phase Information
    for (int k = 0; k < N; k++) {
        Xmag[k] = sqrt(Re[k] * Re[k] + Im[k] * Im[k]);    // Magnitude
        Xphase[k] = atan2(Im[k], Re[k]);                  // Phase
    }
    
    // 4. Design Lowpass Filter
    
    // Apply Lowpass Filter
    for (int k = 0; k < N; k++) {
        double freq = k * (SampleRate / N);  // Convert bin index to frequency
        
        // First Filter
        double H = lowPassXdbPerOctave(freq, fc, order);
        
        // Second Filter for cleaner sound
        H = butterworthLowPass(freq, fc, order);
        
        Xmag[k] *= H;  // Apply the filter to the magnitude, The phase does not change
    }
    
    // Inverse DFT (Reconstruct Time Signal using both magnitude and phase)
    vector<double> filteredSignal(N, 0.0);
    
    for (int n = 0; n < N; n++) {
        double realPart = 0.0;
        double imagPart = 0.0;
        for (int k = 0; k < N; k++) {
            double angle = 2 * M_PI * k * n / N;
            // Rebuild real and imaginary parts from both magnitude and phase
            realPart += Xmag[k] * cos(angle + Xphase[k]);
            imagPart += Xmag[k] * sin(angle + Xphase[k]);
        }
        // Combine real and imaginary parts to form the time-domain signal
        filteredSignal[n] = realPart / N; // Normalize
    }
    
    // After Inverse DFT processing, normalize the signal
    double maxFilteredSignalAbs = *max_element(filteredSignal.begin(), filteredSignal.end(),
                                               [](double a, double b) { return abs(a) < abs(b); });  // Get the largest absolute value
    
    // Normalize to [-1, 1]
    for (int n = 0; n < N; ++n) {
        filteredSignal[n] /= maxFilteredSignalAbs;
    }

    // Set global vector to processed signal
    filteredTable = filteredSignal;
    currentWaveType = WaveType::FILTERED;
    
    // Process filtered signal
    OscEngine(WaveType::FILTERED);
}

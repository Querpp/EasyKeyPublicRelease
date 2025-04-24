#include "Knobs.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// KNOB_DistAlg
int DistAlgConversion(int DistAlg)
{
    // 0 - 205
    if (DistAlg >= 0 && DistAlg <= 205)
        return 1;
    // 206 - 410
    else if (DistAlg <= 410)
        return 2;
    // 411 - 614
    else if (DistAlg <= 614)
        return 3;
    // 615 - 820
    else if (DistAlg <= 820)
        return 4;
    // 821 - 1024
    else if (DistAlg <= 1024)
        return 5;
    return DistAlg; // return unchanged if out of range
}

// KNOB_DistDrive
int DistDriveConversion(int DistDrive)
{
    if (DistDrive < 0) DistDrive = 0;
    if (DistDrive > 1024) DistDrive = 1024;
    // 0 - 99
    return DistDrive * 99 / 1024;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// KNOB_FlgRate
int FlangerRateConversion(int flgRate)
{
    if (flgRate < 0) flgRate = 0;
    if (flgRate > 1023) flgRate = 1023;
    
    int minFreq = 1;    // 1 Hz
    int maxFreq = 20;   // 20 Hz
    
    // Proportional mapping: scale from 0-1023 to 1-20
    return minFreq + (flgRate * (maxFreq - minFreq)) / 1023;
}

// KNOB_FlgMix
int FlangerForceConversion(int flgForce)
{
    if (flgForce < 0) {
        flgForce = 0;
    }
    if (flgForce > 1023) {
        flgForce = 1023;
    }
    
    int minForce = 1;    // Min output: 1
    int maxForce = 100;  // Max output: 100
    
    // Proportional mapping from 0-1023 to 1-100
    return minForce + (flgForce * (maxForce - minForce)) / 1023;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// KNOB_PhsRate
int PhaserRateConversion(int phsRate)
{
    if (phsRate < 0) phsRate = 0;
    if (phsRate > 1023) phsRate = 1023;
    
    int minFreq = 1;    // 1 Hz
    int maxFreq = 20;   // 20 Hz
    
    // Proportional mapping: scale from 0-1023 to 1-20
    return minFreq + (phsRate * (maxFreq - minFreq)) / 1023;
}

// KNOB_PhsMix
int PhaserForceConversion(int phsForce)
{
    if (phsForce < 0) {
        phsForce = 0;
    }
    if (phsForce > 1023) {
        phsForce = 1023;
    }
    
    int minForce = 1;    // Min output: 1
    int maxForce = 100;  // Max output: 100
    
    // Proportional mapping from 0-1023 to 1-100
    return minForce + (phsForce * (maxForce - minForce)) / 1023;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// KNOB_FltLP
int FltLPConversion(int FltLP)
{
    // Ensure the input is within the valid range
    if (FltLP < 0) FltLP = 0;
    if (FltLP > 1023) FltLP = 1023;
    
    // Frequency range
    double minFreq = 20.0;
    double maxFreq = 20000.0;
    
    // Linear mapping from 0-1023 to 20-20000
    double norm = FltLP / 1023.0;  // Normalize to 0.0 - 1.0 range
    double mappedFreq = minFreq + norm * (maxFreq - minFreq);
    
    return static_cast<int>(mappedFreq);  // Return as integer
}

// KNOB_FltQ
int FltQConversion(int FltQ)
{
    // Table of corresponding output values
    const int FltQTable[] = {6, 12, 18, 24, 30, 36, 42, 48, 54, 60, 72, 84, 96};
    const int numValues = sizeof(FltQTable) / sizeof(FltQTable[0]);
    
    // Clamp input
    if (FltQ < 0) FltQ = 0;
    if (FltQ > 1023) FltQ = 1023;
    
    // Map 0–1023 to 0–(numValues - 1)
    int index = (FltQ * numValues) / 1024;
    
    return FltQTable[index];
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// KNOB_EchFreq
int EchFreqConversion(int EchFreq)
{
    if (EchFreq < 0) EchFreq = 0;
    if (EchFreq > 1023) EchFreq = 1023;
    
    int minFreq = 1;    // 1 Hz
    int maxFreq = 20;   // 20 Hz
    
    // Proportional mapping: scale from 0-1023 to 1-20
    return minFreq + (EchFreq * (maxFreq - minFreq)) / 1023;
}

// KNOB_EchMix
int EchoFeedMixConversion(int echFeedMix)
{
    if (echFeedMix < 0) {
        echFeedMix = 0;
    }
    if (echFeedMix > 1023) {
        echFeedMix = 1023;
    }
    
    int minForce = 1;    // Min output: 1
    int maxForce = 100;  // Max output: 100
    
    // Proportional mapping from 0-1023 to 1-100
    return minForce + (echFeedMix * (maxForce - minForce)) / 1023;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// KNOB_VerbDcy
int VerbDcyConversion(int VerbDcy)
{
    if (VerbDcy < 0) VerbDcy = 0;
    if (VerbDcy > 1023) VerbDcy = 1023;
    
    int minForce = 1;    // Min output: 1
    int maxForce = 100;  // Max output: 100
    
    // Proportional mapping from 0-1023 to 1-100
    return minForce + (VerbDcy * (maxForce - minForce)) / 1023;
}


// KNOB_VerbMix
int VerbDriveConversion(int verbDrive)
{
    if (verbDrive < 0) verbDrive = 0;
    if (verbDrive > 1023) verbDrive = 1023;
    
    int minForce = 1;    // Min output: 1
    int maxForce = 100;  // Max output: 100
    
    // Proportional mapping from 0-1023 to 1-100
    return minForce + (verbDrive * (maxForce - minForce)) / 1023;
}

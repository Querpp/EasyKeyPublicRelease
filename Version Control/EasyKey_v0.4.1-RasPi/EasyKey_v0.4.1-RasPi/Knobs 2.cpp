#include "Knobs.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// KNOB_DistAlg
int DistAlgConversion(int DistAlg)
{
    // Invert the reading
    DistAlg = 1023 - DistAlg;
    
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
    // Invert reading
    DistDrive = 1023 - DistDrive;

    // 0 - 99
    return DistDrive * 99 / 1024;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// KNOB_FlgRate
int FlangerRateConversion(int FlgRate)
{
    // Invert reading
    FlgRate = 1023 - FlgRate;
    
    int minFreq = 1;    // 1 Hz
    int maxFreq = 20;   // 20 Hz
    
    // Proportional mapping: scale from 0-1023 to 1-20
    return minFreq + (FlgRate * (maxFreq - minFreq)) / 1023;
}

// KNOB_FlgMix
int FlangerForceConversion(int FlgForce)
{
    // Invert reading
    FlgForce = 1023 - FlgForce;
    
    int minForce = 1;    // Min output: 1
    int maxForce = 100;  // Max output: 100
    
    // Proportional mapping from 0-1023 to 1-100
    return minForce + (FlgForce * (maxForce - minForce)) / 1023;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// KNOB_PhsRate
int PhaserRateConversion(int PhsRate)
{
    // Invert reading
    PhsRate = 1023 - PhsRate;
    
    int minFreq = 1;    // 1 Hz
    int maxFreq = 20;   // 20 Hz
    
    // Proportional mapping: scale from 0-1023 to 1-20
    return minFreq + (PhsRate * (maxFreq - minFreq)) / 1023;
}

// KNOB_PhsMix
int PhaserForceConversion(int PhsForce)
{
    // Invert reading
    PhsForce = 1023 - PhsForce;
    
    int minForce = 1;    // Min output: 1
    int maxForce = 100;  // Max output: 100
    
    // Proportional mapping from 0-1023 to 1-100
    return minForce + (PhsForce * (maxForce - minForce)) / 1023;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// KNOB_FltLP
int FltLPConversion(int FltLP)
{
    // Invert reading
    FltLP = 1023 - FltLP;
    
    // Frequency range
    double minFreq = 20.0;
    double maxFreq = 20000.0;
    
    // Linear mapping from 0-1023 to 20-20000
    double norm = FltLP / 1023.0;  // Normalize to 0.0 - 1.0 range
    double mappedFreq = minFreq + norm * (maxFreq - minFreq);
    
    return static_cast<int>(mappedFreq);
}

// KNOB_FltQ
int FltQConversion(int FltQ)
{
    // Invert reading
    FltQ = 1023 - FltQ;
    
    // Table of corresponding output values
    const int FltQTable[] = {6, 12, 18, 24, 30, 36, 42, 48, 54, 60, 72, 84, 96};
    const int numValues = sizeof(FltQTable) / sizeof(FltQTable[0]);
    
    // Map 0 – 1023 to 0 – (numValues - 1)
    int index = (FltQ * numValues) / 1024;
    
    return FltQTable[index];
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// KNOB_EchFreq
int EchFreqConversion(int EchFreq)
{
    // Invert reading
    EchFreq = 1023 - EchFreq;
    
    int minFreq = 1;    // 1 Hz
    int maxFreq = 20;   // 20 Hz
    
    // Proportional mapping: scale from 0-1023 to 1-20
    return minFreq + (EchFreq * (maxFreq - minFreq)) / 1023;
}

// KNOB_EchMix
int EchoFeedMixConversion(int EchMix)
{
    // Invert reading
    EchMix = 1023 - EchMix;
    
    int minForce = 1;    // Min output: 1
    int maxForce = 100;  // Max output: 100
    
    // Proportional mapping from 0-1023 to 1-100
    return minForce + (EchMix * (maxForce - minForce)) / 1023;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// KNOB_VerbDcy
int VerbDcyConversion(int VerbDcy)
{
    // Invert reading
    VerbDcy = 1023 - VerbDcy;
    
    int minForce = 1;    // Min output: 1
    int maxForce = 100;  // Max output: 100
    
    // Proportional mapping from 0-1023 to 1-100
    return minForce + (VerbDcy * (maxForce - minForce)) / 1023;
}

// KNOB_VerbMix
int VerbDriveConversion(int VerbDrive)
{
    // Invert reading
    VerbDrive = 1023 - VerbDrive;
    
    int minForce = 1;    // Min output: 1
    int maxForce = 100;  // Max output: 100
    
    // Proportional mapping from 0-1023 to 1-100
    return minForce + (VerbDrive * (maxForce - minForce)) / 1023;
}

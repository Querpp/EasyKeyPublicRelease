#include "Knobs.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// ADC Scanning for Potentiometers
void KnobScanner()
{
    // Read GPIO 7 - Oscillator + Effects 1/2
    KNOB_OscOneWave = readPot(7, 0);
    KNOB_DistAlg = readPot(7, 1);
    KNOB_DistDrive = readPot(7, 2);
    KNOB_FlgRate = readPot(7, 3);
    KNOB_FlgMix = readPot(7, 4);
    KNOB_PhsRate = readPot(7, 5);
    KNOB_PhsMix = readPot(7, 6);
    
    // Read GPIO 13 - Effects 2/2
    KNOB_FltLP = readPot(13, 0);
    KNOB_FltQ = readPot(13, 1);
    KNOB_EchFreq = readPot(13, 2);
    KNOB_EchMix = readPot(13, 3);
    KNOB_VerbDcy = readPot(13, 4);
    KNOB_VerbMix = readPot(13, 5);
    
    //-----------------------------------------------------------
    // After collecting values from knobs, convert their numerical data
    OscOneWaveConversion(KNOB_OscOneWave);
    KNOB_DistAlg = DistAlgConversion(KNOB_DistAlg);
    KNOB_DistDrive = DistDriveConversion(KNOB_DistDrive);
    KNOB_FlgRate = FlangerRateConversion(KNOB_FlgRate);
    KNOB_FlgMix = FlangerForceConversion(KNOB_FlgMix);
    KNOB_PhsRate = PhaserRateConversion(KNOB_PhsRate);
    KNOB_PhsMix = PhaserForceConversion(KNOB_PhsMix);
    KNOB_FltLP = FltLPConversion(KNOB_FltLP);
    KNOB_FltQ = FltQConversion(KNOB_FltQ);
    KNOB_EchFreq = EchFreqConversion(KNOB_EchFreq);
    KNOB_EchMix = EchoFeedMixConversion(KNOB_EchMix);
    KNOB_VerbDcy = VerbDcyConversion(KNOB_VerbDcy);
    KNOB_VerbMix = VerbDriveConversion(KNOB_VerbMix);
}

// Read value from specified MCP3008 channel using software CS
int readPot(int csPin, int channel) {
    char tx[3] = {1, (char)((8 + channel) << 4), 0};
    char rx[3] = {0};
    
    gpioWrite(csPin, 0);  // Activate chip select
    int handle = spiOpen(0, 1000000, 0); // SPI0 channel, 1MHz
    if (handle < 0) {
        cerr << "Failed to open SPI device" << endl;
        return -1;
    }
    
    spiXfer(handle, tx, rx, 3);
    spiClose(handle);
    gpioWrite(csPin, 1);  // Deactivate chip select
    
    return ((rx[1] & 3) << 8) | rx[2];
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Oscillators
void OscOneWaveConversion(int WaveOne)
{
    // Invert the reading
    WaveOne = 1023 - WaveOne;
    
    // Evenly divide into 6 options (0–1023 → 0–5)
    int selection = WaveOne * 6 / 1024;
    
    // Set the global currentWaveType
    switch (selection)
    {
        case 0: currentWaveType = WaveType::SAW;        break;
        case 1: currentWaveType = WaveType::SQUARE;     break;
        case 2: currentWaveType = WaveType::SINE;       break;
        case 3: currentWaveType = WaveType::GLORKGLUNK; break;
        case 4: currentWaveType = WaveType::DRUMFILL;   break;
        case 5: currentWaveType = WaveType::DUNE;       break;
        default: currentWaveType = WaveType::SAW;       break; // fallback
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// KNOB_DistAlg
// KNOB_DistAlg
int DistAlgConversion(int DistAlg)
{
    // Invert the reading
    DistAlg = 1023 - DistAlg;
    
    // 0 - 255
    if (DistAlg <= 255)
        return 1;
    // 256 - 511
    else if (DistAlg <= 511)
        return 2;
    // 512 - 767
    else if (DistAlg <= 767)
        return 3;
    // 768 - 1023
    else if (DistAlg <= 1023)
        return 4;
    
    return DistAlg;
}

// KNOB_DistDrive
int DistDriveConversion(int DistDrive)
{
    // Invert reading
    DistDrive = 1023 - DistDrive;

    // 0 - 99
    return DistDrive * 100 / 1024;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// KNOB_FlgRate
int FlangerRateConversion(int FlgRate)
{
    // Invert reading
    FlgRate = 1023 - FlgRate;
    
    // Proportional mapping: scale from 0-1023 to 1-20
    return FlgRate * 20 / 1024 + 1;
}

// KNOB_FlgMix
int FlangerForceConversion(int FlgForce)
{
    // Invert reading
    FlgForce = 1023 - FlgForce;
    
    // 0 – 99
    return FlgForce * 100 / 1024;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// KNOB_PhsRate
int PhaserRateConversion(int PhsRate)
{
    // Invert reading
    PhsRate = 1023 - PhsRate;
    
    // Proportional mapping: scale from 0-1023 to 1-20
    return 1 + (PhsRate * (20 - 1)) / 1023;
}

// KNOB_PhsMix
int PhaserForceConversion(int PhsForce)
{
    // Invert reading
    PhsForce = 1023 - PhsForce;
    
    // 0 – 99
    return PhsForce * 100 / 1024;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// KNOB_FltLP
int FltLPConversion(int FltLP)
{
    // Invert reading
    FltLP = 1023 - FltLP;
    
    // Linear mapping from 0-1023 to 20-20,000
    double norm = FltLP / 1023.0;  // Normalize to 0.0 - 1.0 range
    double mappedFreq = 20 + norm * (20000 - 20);
    
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
    
    // Proportional mapping: scale from 0-1023 to 1-20
    return EchFreq * 20 / 1024 + 1;
}

// KNOB_EchMix
int EchoFeedMixConversion(int EchMix)
{
    // Invert reading
    EchMix = 1023 - EchMix;
    
    // 0 – 99
    return EchMix * 100 / 1024;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// KNOB_VerbDcy
int VerbDcyConversion(int VerbDcy)
{
    // Invert reading
    VerbDcy = 1023 - VerbDcy;

    // 0 – 99
    return VerbDcy * 100 / 1024;
}

// KNOB_VerbMix
int VerbDriveConversion(int VerbDrive)
{
    // Invert reading
    VerbDrive = 1023 - VerbDrive;

    // 0 – 99
    return VerbDrive * 100 / 1024;
}

#ifndef KNOBS_H
#define KNOBS_H

#include "GlobalVariables.h"

// ADC Scanning
void KnobScanner();
int readPot(int csPin, int channel);
void OscOneWaveConversion(int WaveOne);

// Volume
int VolumeConversion(int VolKnob);

// Distortion
int DistAlgConversion(int DistAlg);
int DistDriveConversion(int DistDrive);

// Flanger
int FlangerRateConversion(int flgRate);
int FlangerForceConversion(int flgForce);

// Phaser
int PhaserRateConversion(int phsRate);
int PhaserForceConversion(int phsForce);

// Filter
int FltLPConversion(int FltLP);
int FltQConversion(int FltQ);

// Echo
int EchFreqConversion(int EchFreq);
int EchoFeedMixConversion(int echFeedMix);

// Reverb
int VerbDcyConversion(int VerbDcy);
int VerbDriveConversion(int verbDrive);

#endif // KNOBS_H

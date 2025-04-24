#include "GlobalVariables.h"

// Software
string currentSample =  "    Sine";

// Navigation & Master
int KNOB_MasterVol;
int BUTTON_UPARROW = 0; // 0 = off, 1 = on
int BUTTON_DOWNARROW = 0;
int BUTTON_ENTER = 0;
int BUTTON_LEFTARROW = 0;
int BUTTON_MAP_LFO = 0;

// Effects
int KNOB_DistAlg;
int KNOB_DistDrive;
int KNOB_FlgRate;
int KNOB_FlgForce;
int KNOB_PhsRate;
int KNOB_PhsForce;
int KNOB_FltHP;
int KNOB_FltLP;
int KNOB_EchFreq;
int KNOB_EchFeed;
int KNOB_VerbDcy;
int KNOB_VerbDrive;

// Envelope
int KNOB_ENV_Att;
int KNOB_ENV_Dec;
int KNOB_ENV_Sus;
int KNOB_ENV_Rel;

// LFOs
int KNOB_LFO1_WavFrm;
int KNOB_LFO1_Speed;
int KNOB_LFO2_Wavfrm;
int NOB_LFO2_Speed;

// Sampler
int BUTTON_RecSmpl = 0;
int KNOB_SMPL_Start = 0;
int KNOB_SMPL_End = 100;

// Song Builder
int BUTTON_RecSeq = 0;
int BUTTON_PlayPause = 0;
int BUTTON_DelTake = 0;

// Synthesizer
bool OSC1_isOn;
int KNOB_OSC1_WAVEFORM;
int KNOB_OSC1_COARSE;
int KNOB_OSC1_SEMITONES;
bool OSC2_isOn;
int KNOB_OSC2_WAVEFORM;
int KNOB_OSC2_COARSE;
int KNOB_OSC2_SEMITONES;


// Generate structs
currentPreset g_currentPreset;
LFOmapping g_LFOmapping;
Take g_Take;
Song g_Song;
UsrSample g_UsrSample;
Preset g_Preset;

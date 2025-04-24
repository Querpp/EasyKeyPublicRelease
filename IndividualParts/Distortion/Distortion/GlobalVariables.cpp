#include "GlobalVariables.h"

// LFOs values 1 - 128

// Buttons defined for GPIO pins
int BUTTON_UPARROW = 0;
int BUTTON_DOWNARROW = 1;
int BUTTON_ENTER = 5;
int BUTTON_MAP_LFO = 12;
int BUTTON_APPLYCHANGES = 13;
// Unused
int BUTTON_RECORDSEQUENCE = 14;
int BUTTON_PLAYPAUSE = 15;
int BUTTON_DELETETAKE = 16;
int BUTTON_RECSAMPLE = 20;
int BUTTON_OSC1POWER = 21;
int BUTTON_OSC2POWER = 22;

// Effects Knobs
int KNOB_DistAlg;
int KNOB_DistDrive;
int KNOB_FlgRate;
int KNOB_FlgMix;
int KNOB_PhsRate;
int KNOB_PhsMix;
int KNOB_FltLP;
int KNOB_FltQ;
int KNOB_EchFreq;
int KNOB_EchMix;
int KNOB_VerbDcy;
int KNOB_VerbMix;


// Software
int LengthOfAudioInSeconds = 1;         // Default audio length
int ValueToEdit = 0;                    // UpDownMode
string DrumMachine[5] = {"Kick_1", "Kick_2", "Kick_3", "Kick_4", "Kick_5"};
string currentSample;
vector<double> chosenTable;
vector<double> filteredTable;           // Table with effects processed, passed to each fx
WaveType currentWaveType;

// User-Created Objects
vector<string> usrPresets;
vector<string> usrSongs;
vector<string> usrTakes;
vector<string> LFOmappings;

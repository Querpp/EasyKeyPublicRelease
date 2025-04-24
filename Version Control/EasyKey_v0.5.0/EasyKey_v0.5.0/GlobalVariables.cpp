#include "GlobalVariables.h"

// ---------- Button Controls ----------
int BUTTON_UPARROW = 0;
int BUTTON_DOWNARROW = 1;
int BUTTON_ENTER = 23;
int BUTTON_MAP_LFO = 12;
int BUTTON_APPLYCHANGES = 5;


// ---------- Knob Controls ----------
// Oscillator
int KNOB_OscOneWave;

// Effects
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


// ---------- Synth State ----------
int ValueToEdit = 0; // UpDown mode
string DrumMachine[5] = {"Bass_1", "Brass_1", "Arp_1", "Snare_7", "Harp_2"};
string currentSample;
vector<double> processedTable;
vector<double> chosenTable;
WaveType currentWaveType;


// ---------- User-Created Data ----------
vector<string> usrPresets;
vector<string> usrSongs;
vector<string> usrTakes;
vector<string> LFOmappings;

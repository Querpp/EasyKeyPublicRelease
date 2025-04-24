#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

// Includes for dependencies
#include <algorithm>
#include <cctype>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <termios.h>
#include <thread>
#include <unistd.h>
#include <utility>
#include <vector>
using namespace std;

//-------------------------------------------------------------------------------------------------

// Software
extern string currentSample;

// Navigation & Master
extern int KNOB_MasterVol;
extern int BUTTON_UPARROW;
extern int BUTTON_DOWNARROW;
extern int BUTTON_ENTER;
extern int BUTTON_LEFTARROW;
extern int BUTTON_MAP_LFO;

// Effects
extern int KNOB_DistAlg;
extern int KNOB_DistDrive;
extern int KNOB_FlgRate;
extern int KNOB_FlgForce;
extern int KNOB_PhsRate;
extern int KNOB_PhsForce;
extern int KNOB_FltHP;
extern int KNOB_FltLP;
extern int KNOB_EchFreq;
extern int KNOB_EchFeed;
extern int KNOB_VerbDcy;
extern int KNOB_VerbDrive;

// Envelope
extern int KNOB_ENV_Att;
extern int KNOB_ENV_Dec;
extern int KNOB_ENV_Sus;
extern int KNOB_ENV_Rel;

// LFOs
extern int KNOB_LFO1_WavFrm;
extern int KNOB_LFO1_Speed;
extern int KNOB_LFO2_Wavfrm;
extern int NOB_LFO2_Speed;

// Sampler
extern int BUTTON_RecSmpl;
extern int KNOB_SMPL_Start;
extern int KNOB_SMPL_End;

// Song Builder
extern int BUTTON_RecSeq;
extern int BUTTON_PlayPause;
extern int BUTTON_DelTake;

// Synthesizer
extern bool OSC1_isOn;
extern int KNOB_OSC1_WAVEFORM;
extern int KNOB_OSC1_COARSE;
extern int KNOB_OSC1_SEMITONES;
extern bool OSC2_isOn;
extern int KNOB_OSC2_WAVEFORM;
extern int KNOB_OSC2_COARSE;
extern int KNOB_OSC2_SEMITONES;

// Structures
struct currentPreset{};
struct currentSample{};
struct LFOmapping{};
struct Take{};
struct Song{};
struct UsrSample{};
struct Preset{};

// Communicate to cpp
extern currentPreset g_currentPreset;
extern LFOmapping g_LFOmapping;

#endif // GLOBALVARIABLES_H

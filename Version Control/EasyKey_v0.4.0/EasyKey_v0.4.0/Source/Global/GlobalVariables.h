#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <ncurses.h>
#include <random>
#include <string>
#include <termios.h>
#include <thread>
#include <unistd.h>
#include <utility>
#include <vector>

using namespace std;

// -------------------------------------------------------------------------------------------------


// Enum for waveform types
enum class WaveType {
    SAW,
    SQUARE,
    SINE,
    GLORKGLUNK,
    DRUMFILL,
    DUNE,
    FILTERED
};

// ADC Scanning
#define SPI_CHANNEL 1
#define SPI_SPEED 1350000
#define durationSeconds 0.2     // Duration in seconds
#define SampleRate 44100        // sampling rate



// Navigation & Master Controls
extern int BUTTON_UPARROW;
extern int BUTTON_DOWNARROW;
extern int BUTTON_ENTER;
extern int BUTTON_MAP_LFO;
extern int BUTTON_APPLYCHANGES;
// Unused
extern int BUTTON_RECORDSEQUENCE;
extern int BUTTON_PLAYPAUSE;
extern int BUTTON_DELETETAKE;
extern int BUTTON_RECSAMPLE;
extern int BUTTON_OSC1POWER;
extern int BUTTON_OSC2POWER;

// Effects Knobs
extern int KNOB_DistAlg;
extern int KNOB_DistDrive;
extern int KNOB_FlgRate;
extern int KNOB_FlgMix;
extern int KNOB_PhsRate;
extern int KNOB_PhsMix;
extern int KNOB_FltLP;
extern int KNOB_FltQ;
extern int KNOB_EchFreq;
extern int KNOB_EchMix;
extern int KNOB_VerbDcy;
extern int KNOB_VerbMix;


// Software
extern int LengthOfAudioInSeconds;
extern int ValueToEdit;
extern string currentSample;
extern vector<double> filteredTable;
extern vector<double> chosenTable;
extern WaveType currentWaveType;

// User-Created Objects
extern vector<string> usrPresets;
extern vector<string> usrSongs;
extern vector<string> usrTakes;
extern vector<string> LFOmappings;


#endif // GLOBALVARIABLES_H

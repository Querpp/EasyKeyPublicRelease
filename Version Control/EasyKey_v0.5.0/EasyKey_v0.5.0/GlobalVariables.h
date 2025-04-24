#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

// ---------- Standard Library ----------
#include <algorithm>
#include <cctype>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <random>
#include <string>
#include <thread>
#include <unistd.h>
#include <sys/stat.h>
#include <termios.h>
#include <utility>
#include <vector>

// ---------- System-Specific ----------
#include <ncurses.h>
#include <pigpio.h>
#include <alsa/asoundlib.h>
using namespace std;


// ---------- Constants ----------
#define DurationSeconds 0.2
#define SampleRate 44100
#define Amplitude 32767
#define SPI_CHANNEL 1
#define SPI_SPEED 1350000


// ---------- Enums ----------
enum class WaveType {
    SAW,
    SQUARE,
    SINE,
    GLORKGLUNK,
    DRUMFILL,
    DUNE,
    PROCESSED
};


// ---------- Button Controls ----------
extern int BUTTON_UPARROW;
extern int BUTTON_DOWNARROW;
extern int BUTTON_ENTER;
extern int BUTTON_MAP_LFO;
extern int BUTTON_APPLYCHANGES;


// ---------- Knob Controls ----------
// Oscillator
extern int KNOB_OscOneWave;

// Effects
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


// ---------- Synth State ----------
extern int ValueToEdit;
extern string DrumMachine[5];
extern string currentSample;
extern vector<double> processedTable;
extern vector<double> chosenTable;
extern WaveType currentWaveType;


// ---------- User-Created Data ----------
extern vector<string> usrPresets;
extern vector<string> usrSongs;
extern vector<string> usrTakes;
extern vector<string> LFOmappings;

#endif // GLOBALVARIABLES_H

#include "MenuFunctions.h"
#include "AudioPlayer.h"

vector<MenuItem> choices;

// MenuItem constructor definition
MenuItem::MenuItem(const string& n, int i, bool minisub, bool has_subs, bool open)
: hasMiniSubs(has_subs), isMiniSub(minisub), isOpen(open), indentLevel(i), name(n) {}

void clearScreen() {
    cout << "\033[2J\033[H";
}

void ncursesInitialize()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

void openingAnimation()
{
    const char* messages[] = {"Loading EasyKey   ", "Loading EasyKey.  ", "Loading EasyKey.. ", "Loading EasyKey..."};
    for (const char* msg : messages)
    {
        cout << "\r" << msg << flush;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << "\r          \r";
}

// Pick current sound
void setCurrSample(string newSample) {
    currentSample = newSample;
}


// Play audio by name
void playAudioByName(int highlight, const string& name) {
    if (choices[highlight].name == name) {
        setCurrSample(name);
        playCurrentSample(currentSample);
    }
}

// Play audio based on category and count
void playAudioFromCategory(int highlight, const string& category, int count)
{
    vector<string> prefixes = {"        ", "      "}; // Different indentation levels
    
    for (int i = 1; i <= count; ++i)
    {
        for (const auto& prefix : prefixes)
        {
            string name = prefix + category + "_" + to_string(i);
            if (choices[highlight].name == name) {
                setCurrSample(name);
                playCurrentSample(currentSample);
                return; // Exit both loops once the match is found
            }
        }
    }
}


// LEVEL ONE - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void addLevelOne() {
    choices.push_back(MenuItem("Apply Changes", 0));
    choices.push_back(MenuItem("Effects", 0));
    choices.push_back(MenuItem("Synthesizer Mode", 0));
    choices.push_back(MenuItem("Sampler Mode", 0));
    choices.push_back(MenuItem("Presets", 0));
    choices.push_back(MenuItem("Song Builder", 0));
    choices.push_back(MenuItem("LFO Mappings", 0));
    choices.push_back(MenuItem("Exit", 0));
}

// LEVEL TWO -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
void addLevelTwo(int startIndex, int subIndent)
{
    if (choices[startIndex].name == "Effects") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("  Distortion", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("  Flanger", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("  Phaser", subIndent));
        choices.insert(choices.begin() + startIndex + 4, MenuItem("  Filter", subIndent));
        choices.insert(choices.begin() + startIndex + 5, MenuItem("  Echo", subIndent));
        choices.insert(choices.begin() + startIndex + 6, MenuItem("  Reverb", subIndent));
    }
    
    if (choices[startIndex].name == "Synthesizer Mode") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("  Choose Waveform", subIndent));
    }
    
    if (choices[startIndex].name == "Sampler Mode") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("  Record Sample", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("  Choose Sample", subIndent));
    }
    
    if (choices[startIndex].name == "Presets") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("  Save as Preset", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("  View Presets", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("  Delete Preset", subIndent));
    }
    
    if (choices[startIndex].name == "Song Builder") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("  New Song", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("  Load Song", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("  Record Sequence", subIndent));
        choices.insert(choices.begin() + startIndex + 4, MenuItem("  Delete Sequence", subIndent));
        choices.insert(choices.begin() + startIndex + 5, MenuItem("  Delete Song", subIndent));
    }
    
    if (choices[startIndex].name == "LFO Mappings") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("  Create LFO", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("  Display Mappings", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("  Remove Mapping", subIndent));
    }
}

// LEVEL THREE --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
void addLevelThree(int startIndex, int subIndent)
{
    // EFFECTS
    if (choices[startIndex].name == "  Distortion") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Display Distortion Settings", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    Edit Distortion Algorithm", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("    Edit Distortion Drive", subIndent));
    }
    if (choices[startIndex].name == "  Flanger") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Display Flanger Settings", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    Edit Flanger Rate", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("    Edit Flanger Mix", subIndent));
    }
    if (choices[startIndex].name == "  Phaser") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Display Phaser Settings", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    Edit Phaser Rate", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("    Edit Phaser Mix", subIndent));
    }
    
    if (choices[startIndex].name == "  Filter") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Display Filter Settings", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    Edit Lowpass Frequency", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("    Edit Lowpass Slope", subIndent));
    }
    if (choices[startIndex].name == "  Echo") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Display Echo Settings", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    Edit Echo Frequency", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("    Edit Echo Mix", subIndent));
    }
    if (choices[startIndex].name == "  Reverb") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Display Reverb Settings", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    Edit Reverb Decay", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("    Edit Reverb Mix", subIndent));
    }
    
    // SYNTHESIZER MODE
    if (choices[startIndex].name == "  Choose Waveform") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Saw", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    Square", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("    Sine", subIndent));
        choices.insert(choices.begin() + startIndex + 4, MenuItem("    Glorkglunk", subIndent));
        choices.insert(choices.begin() + startIndex + 5, MenuItem("    Drum Fill", subIndent));
        choices.insert(choices.begin() + startIndex + 6, MenuItem("    Dune", subIndent));
    }
    
    // SAMPLER MODE
    if (choices[startIndex].name == "  Choose Sample") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Synths", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    Instruments", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("    Drums", subIndent));
        choices.insert(choices.begin() + startIndex + 4, MenuItem("    Misc.", subIndent));
    }
    
    // PRESETS
    if (choices[startIndex].name == "  View Presets") {
        for (size_t i = 0; i < usrPresets.size(); ++i) {
            choices.insert(choices.begin() + startIndex + 1 + i, MenuItem(usrPresets[i], subIndent));
        }
    }
    if (choices[startIndex].name == "  Delete Preset") {
        for (size_t i = 0; i < usrPresets.size(); ++i) {
            choices.insert(choices.begin() + startIndex + 1 + i, MenuItem(usrPresets[i], subIndent));
        }
    }
    
    // SONG BUILDER
    if (choices[startIndex].name == "  Load Song") {
        for (size_t i = 0; i < usrSongs.size(); ++i) {
            choices.insert(choices.begin() + startIndex + 1 + i, MenuItem(usrSongs[i], subIndent));
        }
    }
    if (choices[startIndex].name == "  Record Sequence") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Press any key (Press 'q' to quit): ", subIndent, true));
        // Enable key recording
    }
    if (choices[startIndex].name == "  Delete Sequence")
    {
        for (size_t i = 0; i < usrTakes.size(); ++i) {
            choices.insert(choices.begin() + startIndex + 1 + i, MenuItem(usrTakes[i], subIndent));
        }
    }
    
    if (choices[startIndex].name == "  Delete Song")
    {
        for (size_t i = 0; i < usrSongs.size(); ++i) {
            choices.insert(choices.begin() + startIndex + 1 + i, MenuItem(usrSongs[i], subIndent));
        }
    }
    
    // LFO MAPPINGS
    if (choices[startIndex].name == "  Display Mappings")
    {
        for (size_t i = 0; i < LFOmappings.size(); ++i) {
            choices.insert(choices.begin() + startIndex + 1 + i, MenuItem(LFOmappings[i], subIndent));
        }
    }
    if (choices[startIndex].name == "  Remove Mapping")
    {
        for (size_t i = 0; i < LFOmappings.size(); ++i) {
            choices.insert(choices.begin() + startIndex + 1 + i, MenuItem(LFOmappings[i], subIndent));
        }
    }
}

// L E V E L  F O U R ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- --
void addLevelFour(int startIndex, int subIndent)
{
    // EFFECTS
    // Distortion
    if (choices[startIndex].name == "    Display Distortion Settings") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem(string("        ") + "Current Distortion Algorithm: " + to_string(KNOB_DistAlg), subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem(string("        ") + "Current Distortion Drive: " + to_string(KNOB_DistDrive), subIndent));
    }
    // Flanger
    if (choices[startIndex].name == "    Display Flanger Settings") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem(string("        ") + "Current Flanger Rate: " + to_string(KNOB_FlgRate), subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem(string("        ") + "Current Flanger Mix: " + to_string(KNOB_FlgMix), subIndent));
    }
    // Phaser
    if (choices[startIndex].name == "    Display Phaser Settings") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem(string("        ") + "Current Phaser Rate: " + to_string(KNOB_PhsRate), subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem(string("        ") + "Current Phaser Mix: " + to_string(KNOB_PhsMix), subIndent));
    }
    // Filter
    if (choices[startIndex].name == "    Display Filter Settings") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem(string("        ") + "Current Cutoff Frequency: " + to_string(KNOB_FltLP), subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem(string("        ") + "Current Slope: " + to_string(KNOB_FltQ), subIndent));
    }
    if (choices[startIndex].name == "    Edit Lowpass Frequency") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("        Press up or down to change frequency in Hz. Press q to exit", subIndent));
    }
    if (choices[startIndex].name == "    Edit Lowpass Slope") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("        Press up or down to change slope value. Press q to exit", subIndent));
    }
    // Echo
    if (choices[startIndex].name == "    Display Echo Settings") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem(string("        ") + "Current Echo Frequency: " + to_string(KNOB_EchFreq), subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem(string("        ") + "Current Echo Mix: " + to_string(KNOB_EchMix), subIndent));
    }
    // Reverb
    if (choices[startIndex].name == "    Display Reverb Settings") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem(string("        ") + "Current Reverb Decay: " + to_string(KNOB_VerbDcy), subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem(string("        ") + "Current Reverb Mix: " + to_string(KNOB_VerbMix), subIndent));
    }
    
    
    // SAMPLER MODE
    if (choices[startIndex].name == "    Synths") {
        vector<string> synths = {"      Arps", "      Basses", "      Leads", "      Pads"};
        for (size_t i = 0; i < synths.size(); ++i) {
            choices.insert(choices.begin() + startIndex + 1 + i, MenuItem(synths[i], subIndent, true));
        }
    }
    if (choices[startIndex].name == "    Instruments") {
        vector<string> instruments = {"      Brass", "      Choir", "      Strings", "      Harp", "      Guitar"};
        
        for (size_t i = 0; i < instruments.size(); ++i) {
            choices.insert(choices.begin() + startIndex + 1 + i, MenuItem(instruments[i], subIndent));
        }
    }
    if (choices[startIndex].name == "    Drums") {
        vector<string> drumTypes = {
            "      Kicks", "      Snares", "      Claps", "      Crashes",
            "      HiHats", "      Rides", "      Toms", "      Other"
        };
        for (size_t i = 0; i < drumTypes.size(); ++i) {
            choices.insert(choices.begin() + startIndex + 1 + i, MenuItem(drumTypes[i], subIndent, true));
        }
    }
    if (choices[startIndex].name == "    Misc.") {
        for (int i = 1; i <= 18; ++i) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("      Misc_" + to_string(i), subIndent, true));
        }
    }
}

// L E V E L  F I V E ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
void addLevelFive(int startIndex, int subIndent)
{
    // SYNTHS------------------------------------------------------------------
    // Arps
    if (choices[startIndex].name == "      Arps") {
        for (int i = 1; i <= 5; ++i) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("        Arp_" + to_string(i), subIndent, true));
        }
    }
    // Basses
    if (choices[startIndex].name == "      Basses") {
        for (int i = 1; i <= 20; i++) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("        Bass_" + to_string(i), subIndent, true));
        }
    }
    // Leads
    if (choices[startIndex].name == "      Leads") {
        for (int i = 1; i <= 8; i++) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("        Lead_" + to_string(i), subIndent, true));
        }
    }
    // Pads
    if (choices[startIndex].name == "      Pads") {
        for (int i = 1; i <= 8; i++) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("        Pad_" + to_string(i), subIndent, true));
        }
    }
    
    // INSTRUMENTS-------------------------------------------------------------
    // Brass
    if (choices[startIndex].name == "      Brass") {
        for (int i = 1; i <= 5; i++) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("        Brass_" + to_string(i), subIndent, true));
        }
    }
    // Choir
    if (choices[startIndex].name == "      Choir") {
        for (int i = 1; i <= 5; i++) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("        Choir_" + to_string(i), subIndent, true));
        }
    }
    // Strings
    if (choices[startIndex].name == "      Strings") {
        for (int i = 1; i <= 5; i++) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("        Strings_" + to_string(i), subIndent, true));
        }
    }
    // Harp
    if (choices[startIndex].name == "      Harp") {
        for (int i = 1; i <= 4; i++) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("        Harp_" + to_string(i), subIndent, true));
        }
    }
    // Guitar
    if (choices[startIndex].name == "      Guitar") {
        for (int i = 1; i <= 5; i++) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("        Guitar_" + to_string(i), subIndent, true));
        }
    }
    
    // DRUMS-------------------------------------------------------------------
    // Kicks
    if (choices[startIndex].name == "      Kicks") {
        for (int i = 1; i <= 10; i++) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("        Kick_" + to_string(i), subIndent, true));
        }
    }
    // Snares
    if (choices[startIndex].name == "      Snares") {
        for (int i = 1; i <= 10; i++) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("        Snare_" + to_string(i), subIndent, true));
        }
    }
    // Claps
    if (choices[startIndex].name == "      Claps") {
        for (int i = 1; i <= 3; i++) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("        Clap_" + to_string(i), subIndent, true));
        }
    }
    // Crashes
    if (choices[startIndex].name == "      Crashes") {
        for (int i = 1; i <= 3; i++) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("        Crash_" + to_string(i), subIndent, true));
        }
    }
    // HiHats
    if (choices[startIndex].name == "      HiHats") {
        for (int i = 1; i <= 5; i++) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("        HiHat_" + to_string(i), subIndent, true));
        }
    }
    // Rides
    if (choices[startIndex].name == "      Rides") {
        for (int i = 1; i <= 5; i++) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("        Ride_" + to_string(i), subIndent, true));
        }
    }
    // Toms
    if (choices[startIndex].name == "      Toms") {
        for (int i = 1; i <= 5; i++) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("        Tom_" + to_string(i), subIndent, true));
        }
    }
    // Other
    if (choices[startIndex].name == "      Other") {
        for (int i = 1; i <= 5; i++) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("        Other_" + to_string(i), subIndent, true));
        }
    }
}

#include "menuFunctions.h"

vector<MenuItem> choices;

// MenuItem constructor definition
MenuItem::MenuItem(const string& n, int i, bool minisub, bool has_subs, bool open)
: hasMiniSubs(has_subs), isMiniSub(minisub), isOpen(open), indentLevel(i), name(n) {}


// LEVEL ONE - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void addLevelOne() {
    //    choices.push_back(MenuItem("DEBUG - MIDIencoder", 0));
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
    if (choices[startIndex].name == "Synthesizer Mode") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("  Choose Waveform", subIndent));
    }
    
    if (choices[startIndex].name == "Sampler Mode") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("  Record Sample", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("  Choose Sample", subIndent));
        
    }
    if (choices[startIndex].name == "Presets") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("  View Presets", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("  Save as Preset", subIndent));
    }
    if (choices[startIndex].name == "Song Builder") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("  Record Sequence", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("  Delete Take", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("  Select Song", subIndent));
        choices.insert(choices.begin() + startIndex + 4, MenuItem("  Delete Song", subIndent));
    }
    if (choices[startIndex].name == "LFO Mappings") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("  Display Mappings", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("  Remove Mapping", subIndent));
    }
}

// LEVEL THREE --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
void addLevelThree(int startIndex, int subIndent)
{
    // SYNTHESIZER MODE
    if (choices[startIndex].name == "  Choose Waveform") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    QuerppGrowl", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    Saw", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("    Sine", subIndent));
        choices.insert(choices.begin() + startIndex + 4, MenuItem("    Square", subIndent));
        choices.insert(choices.begin() + startIndex + 5, MenuItem("    Triangle", subIndent));
        choices.insert(choices.begin() + startIndex + 6, MenuItem("    Glorkglunk", subIndent));
        choices.insert(choices.begin() + startIndex + 7, MenuItem("    Dune", subIndent));
        choices.insert(choices.begin() + startIndex + 8, MenuItem("    Grime", subIndent));
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
        // List created presets
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Preset #: B7Sh3", subIndent, true));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    Preset #: M8x1q", subIndent, true));
    }
    if (choices[startIndex].name == "  Save as Preset") {
        // Send letter P to currentSynthSettings
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Your Preset is: ", subIndent, true));
    }
    
    // SONG BUILDER
    if (choices[startIndex].name == "  Record Sequence") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Press any key (Press 'q' to quit): ", subIndent, true));
    }
    if (choices[startIndex].name == "  Delete Take") {
        // Display created takes
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Take 1: 8bA7m", subIndent, true));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    Take 2: VB8fj", subIndent, true));
    }
    if (choices[startIndex].name == "  Select Song") {
        // Could use the number after startIndex for what # song is
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Song 1: 42dj9", subIndent, true));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    Song 2: M5Cs0", subIndent, true));
    }
    if (choices[startIndex].name == "  Delete Song") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Song 1: 42dj9", subIndent, true));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    Song 2: M5Cs0", subIndent, true));
    }
    
    // LFO MAPPINGS
    if (choices[startIndex].name == "  Display Mappings") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    LFO_1 -> DistortionDrive", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    LFO_1 -> EchoFrequency", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("    LFO_2 -> FlangerRate", subIndent));
    }
    if (choices[startIndex].name == "  Remove Mapping") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    LFO_1 -> DistortionDrive", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    LFO_1 -> EchoFrequency", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("    LFO_2 -> FlangerRate", subIndent));
    }
}

// L E V E L  F O U R ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- --
void addLevelFour(int startIndex, int subIndent)
{
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
        for (int i = 1; i <= 19; ++i) {
            choices.insert(choices.begin() + startIndex + i,
                           MenuItem("      Misc_" + to_string(i), subIndent, true));
        }
    }
}




// L E V E L  F I V E ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
void addLevelFive(int startIndex, int subIndent)
{
    // SYNTHS------------------------------------------------------------------
    // Arps
    if (choices[startIndex].name == "      Arps") {
        for (int i = 1; i <= 7; ++i) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("        Arp_" + to_string(i), subIndent, true));
        }
    }
    // Basses
    if (choices[startIndex].name == "      Basses") {
        for (int i = 1; i <= 23; i++) {
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
        for (int i = 1; i <= 12; i++) {
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
        for (int i = 1; i <= 6; i++) {
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
        for (int i = 1; i <= 7; i++) {
            choices.insert(choices.begin() + startIndex + i, MenuItem("        Other_" + to_string(i), subIndent, true));
        }
    }
}

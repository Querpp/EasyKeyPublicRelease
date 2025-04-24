/*******************************************************
 * File Name:    EasyKey v0.5.0 - Capstone Expo Version
 *
 * Description:
 *  - Distortion effect added
 *  - Drum machine implemented
 *  - System minimized to core functional components
 *  - Global variables organized
 *  - Phaser effect added
 *  - Preset saving/loading mechanics implemented
 *  - Internal wiring reduced
 *  - KeyPress module removed
 *  - Spacebar now functions as Enter
 *
 * Authors:      Ethan Laptew, David Frost, Courtney Jones
 * Created:      2025-04-22
 * Version:      v0.5.0
 * License:      Public Domain / No Rights Reserved
 ********************************************************/

#include "AudioFormats.h"
#include "AudioPlayer.h"
#include "Buttons.h"
#include "Distortion.h"
#include "DrumMachine.h"
#include "Filter.h"
#include "GlobalVariables.h"
#include "Knobs.h"
#include "MenuFunctions.h"
#include "OscEngine.h"
#include "Paths.h"
#include "Phaser.h"
#include "PresetSaving.h"
#include "UpDown.h"
#include "UserCreate.h"

// Clean up generated files when exiting program
void cleanGeneratedFiles() {
    cout << "Cleaning up generated files...\n";
    
    remove("audioPlayerDEBUG.txt");
    remove("./Resources/SampleLibrary/OriginalNoise.wav");
    
    for (int i = 0; i <= 17; ++i) {
        string filename = "./Resources/SampleLibrary/OscillatorWaveform_" + to_string(i) + ".wav";
        remove(filename.c_str());
    }
}

// Close menu function
void closeMenu(vector<MenuItem>& choices, const string& name, int eraseCount) {
    for (int i = 0; i < choices.size(); ++i) {
        if (choices[i].name == name && choices[i].isOpen) {
            choices.erase(choices.begin() + i + 1, choices.begin() + i + eraseCount + 1); // # + 1
            choices[i].isOpen = false;
            break;
        }
    }
}

void applyChanges()
{
    // Process all effects
    // 1. Distortion
    DistortionEffect(KNOB_DistAlg, KNOB_DistDrive);
    // 2. Flanger
    // 3. Phaser
//    PhaserEffect(KNOB_PhsRate, KNOB_PhsMix);
    // 4. Filter
    LowpassFilter(KNOB_FltLP, KNOB_FltQ);
    // 5. Echo
    // 6. Reverb
}




//-----------------------------------------------------------------------------------------------------------------------------------------

int main()
{
    // GPIO Button
    if (gpioInitialise() < 0) {
        cerr << "Failed to initialize" << endl;
        return 1;
    }
    
    // Initialize Buttons
    initButtons();

    clearScreen();
    ncursesInitialize();
    openingAnimation();
    
    int height = 18, width = 60, startY = 0, startX = 0; // for raspi, X/Y = 0
    WINDOW* menuWindow = newwin(height, width, startY, startX);
    box(menuWindow, 0, 0);
    int highlight = 0, choice = 0, scrollOffset = 0;
    keypad(menuWindow, TRUE);
    
    addLevelOne();
    
    // Initialize global values
    usrPresets.push_back("    No Presets");
    usrSongs.push_back("    No Songs");
    usrTakes.push_back("    No Sequences");
    LFOmappings.push_back("    No LFOs");
    currentWaveType = WaveType::SAW;
    currentSample = "Brass_1";
    
    // Initialize filter values
    KNOB_FltLP = 500;
    KNOB_FltQ = 10;
    KNOB_DistAlg = 1;
    KNOB_DistDrive = 90;    
    
    while(true)
    {
        // Clear window and redraw border
        wclear(menuWindow);
        box(menuWindow, 0, 0);
        
        // Calculate the maximum number of items that can be displayed
        int num_items_to_display = min(height - 2, (int)choices.size() - scrollOffset);
        
        // Display menu with scrolling
        for (int i = 0; i < num_items_to_display; i++)
        {
            int index = i + scrollOffset;
            if (index == highlight) {
                wattron(menuWindow, A_REVERSE);
            }
            mvwprintw(menuWindow, i + 1, choices[index].indentLevel * 2 + 1, "%s", choices[index].name.c_str());
            wattroff(menuWindow, A_REVERSE);
        }
        
        // Scan and convert all knob values and set global variables
        KnobScanner();
        
        
        //------------------------------------------------------
        // GPIO Buttons
        nodelay(menuWindow, TRUE);    // make wgetch non-blocking
        choice = wgetch(menuWindow);
        
        // Menu Navigation
        int upState = gpioRead(BUTTON_UPARROW);
        int downState = gpioRead(BUTTON_DOWNARROW);
        if (upState == 0) {
            choice = KEY_UP;
        } else if (downState == 0) {
            choice = KEY_DOWN;
        }
        
        // Apply Changes
        int applyChangesState = gpioRead(BUTTON_APPLYCHANGES);
        if (applyChangesState == 0) {
            applyChanges();
        }
        
        // Enter Button
        int enterState = gpioRead(BUTTON_ENTER);
        if (enterState == 0) {
            choice = 10;
        }
        gpioDelay(150000); // debounce / pacing delay
        //------------------------------------------------------
        
        
        switch(choice)
        {
            case KEY_UP:
                (highlight > 0) ? highlight-- : highlight;
                (highlight < scrollOffset) ? --scrollOffset : scrollOffset;
                break;
            case KEY_DOWN:
                (highlight < choices.size() - 1) ? highlight++ : highlight;
                (highlight >= scrollOffset + height -2) ? scrollOffset++ : scrollOffset;
                break;
                
                // Keyboard
            case 'a': // C3
                playCurrentSample("OscillatorWaveform_0");
                break;
            case 'w': // C#3
                playCurrentSample("OscillatorWaveform_1");
                break;
            case 's': // D3
                playCurrentSample("OscillatorWaveform_2");
                break;
            case 'e': // D#3
                playCurrentSample("OscillatorWaveform_3");
                break;
            case 'd': // E3
                playCurrentSample("OscillatorWaveform_4");
                break;
            case 'f': // F3
                playCurrentSample("OscillatorWaveform_5");
                break;
            case 't': // F#3
                playCurrentSample("OscillatorWaveform_6");
                break;
            case 'g': // G3
                playCurrentSample("OscillatorWaveform_7");
                break;
            case 'y': // G#3
                playCurrentSample( "OscillatorWaveform_8");
                break;
            case 'h': // A3
                playCurrentSample("OscillatorWaveform_9");
                break;
            case 'u': // A#2
                playCurrentSample("OscillatorWaveform_10");
                break;
            case 'j': // B3
                playCurrentSample("OscillatorWaveform_11");
                break;
            case 'k': // C4
                playCurrentSample("OscillatorWaveform_12");
                break;
            case 'o': // C#4
                playCurrentSample("OscillatorWaveform_13");
                break;
            case 'l': // D4
                playCurrentSample("OscillatorWaveform_14");
                break;
            case 'p': // D#4
                playCurrentSample("OscillatorWaveform_15");
                break;
            case ';': // E4
                playCurrentSample("OscillatorWaveform_16");
                break;
            case '\'': // F4
                playCurrentSample("OscillatorWaveform_17");
                break;
                // Drum Machine
            case 'z':
                playCurrentSample(DrumMachine[0]);
                break;
            case 'x':
                playCurrentSample(DrumMachine[1]);
                break;
            case 'c':
                playCurrentSample(DrumMachine[2]);
                break;
            case 'v':
                playCurrentSample(DrumMachine[3]);
                break;
            case 'b':
                playCurrentSample(DrumMachine[4]);
                break;
            case '=':
                applyChanges();
                break;
                
                // Menu System
            case ' ':
            case 10: {
                
// L E V E L  O N E - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                
                // APPLY CHANGES
                if (choices[highlight].name == "Apply Changes")
                {
                    applyChanges();
                }
                
                // EFFECTS
                if (choices[highlight].name == "Effects") {
                    if (choices[highlight].isOpen) {
                        // Close Level Three
                        closeMenu(choices, "    Display Distortion Settings", 2);
                        closeMenu(choices, "    Display Flanger Settings", 2);
                        closeMenu(choices, "    Display Phaser Settings", 2);
                        closeMenu(choices, "    Display Filter Settings", 2);
                        closeMenu(choices, "    Edit Lowpass Frequency", 1);
                        closeMenu(choices, "    Edit Lowpass Slope", 1);
                        closeMenu(choices, "    Display Echo Settings", 2);
                        closeMenu(choices, "    Display Reverb Settings", 2);
                        // Close Level Two
                        closeMenu(choices, "  Distortion", 3);
                        closeMenu(choices, "  Flanger", 3);
                        closeMenu(choices, "  Phaser", 3);
                        closeMenu(choices, "  Filter", 3);
                        closeMenu(choices, "  Echo", 3);
                        closeMenu(choices, "  Reverb", 3);
                        // Close Effects itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 7);  // # + 1
                        choices[highlight].isOpen = false;  // Mark as closed
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelTwo(highlight, newIndent);
                        choices[highlight].isOpen = true;   // Mark as open
                    }
                }
                
                // SYNTHESIZER MODE
                if (choices[highlight].name == "Synthesizer Mode") {
                    if (choices[highlight].isOpen) {
                        // Close Level 2
                        closeMenu(choices, "  Choose Waveform", 6);
                        // Close Synthesizer itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 2);  // # + 1
                        choices[highlight].isOpen = false;  // Mark as closed
                    } else {
                        // CURRENTLY CLOSED
                        int newIndent = choices[highlight].indentLevel;
                        addLevelTwo(highlight, newIndent);
                        choices[highlight].isOpen = true;   // Mark as open
                    }
                }
                
                // SAMPLER MODE
                if (choices[highlight].name == "Sampler Mode") {
                    if (choices[highlight].isOpen)
                    {
                        // CLOSE LEVEL FIVE
                        closeMenu(choices, "      Arps", 5);
                        closeMenu(choices, "      Basses", 20);
                        closeMenu(choices, "      Leads", 8);
                        closeMenu(choices, "      Pads", 8);
                        closeMenu(choices, "      Brass", 5);
                        closeMenu(choices, "      Choir", 5);
                        closeMenu(choices, "      Strings", 5);
                        closeMenu(choices, "      Harp", 4);
                        closeMenu(choices, "      Guitar", 5);
                        closeMenu(choices, "      Kicks", 10);
                        closeMenu(choices, "      Snares", 10);
                        closeMenu(choices, "      Claps", 3);
                        closeMenu(choices, "      Crashes", 3);
                        closeMenu(choices, "      HiHats", 5);
                        closeMenu(choices, "      Rides", 5);
                        closeMenu(choices, "      Toms", 5);
                        closeMenu(choices, "      Other", 5);
                        // CLOSE LEVEL FOUR
                        closeMenu(choices, "    Synths", 4);
                        closeMenu(choices, "    Instruments", 5);
                        closeMenu(choices, "    Drums", 8);
                        closeMenu(choices, "    Misc.", 18);
                        // CLOSE LEVEL THREE
                        closeMenu(choices, "  Choose Sample", 4);
                        // Close Sampler Mode itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 3);  // # + 1
                        choices[highlight].isOpen = false;
                    }
                    else {
                        // CURRENTLY CLOSED
                        int newIndent = choices[highlight].indentLevel;
                        addLevelTwo(highlight, newIndent);  // Open level two if currently closed
                        choices[highlight].isOpen = true;
                    }
                }
                
                // Choice == PRESETS
                if (choices[highlight].name == "Presets") {
                    if (choices[highlight].isOpen) {
                        // Close Level Two
                        closeMenu(choices, "  View Presets", static_cast<int>(usrPresets.size()));
                        closeMenu(choices, "  Delete Preset", static_cast<int>(usrPresets.size()));
                        // Close Presets itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 4);  // # + 1
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelTwo(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                
                // Choice == SONG BUILDER
                if (choices[highlight].name == "Song Builder") {
                    if (choices[highlight].isOpen) {
                        // CLOSE LEVEL TWO
                        closeMenu(choices, "  Load Song", static_cast<int>(usrSongs.size()));
                        closeMenu(choices, "  Record Sequence", 1);
                        closeMenu(choices, "  Delete Sequence", static_cast<int>(usrTakes.size()));
                        closeMenu(choices, "  Delete Song", static_cast<int>(usrSongs.size()));
                        // Close Song Builder itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 6);  // # + 1
                        choices[highlight].isOpen = false; // Mark Song Builder as closed
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelTwo(highlight, newIndent); // Add sub-options for Song Builder
                        choices[highlight].isOpen = true;  // Mark Song Builder as open
                    }
                }
                
                // Choice == LFO MAPPINGS
                if (choices[highlight].name == "LFO Mappings") {
                    if (choices[highlight].isOpen) {
                        // CLOSE LEVEL THREE
                        closeMenu(choices, "  Display Mappings", static_cast<int>(LFOmappings.size()));
                        closeMenu(choices, "  Remove Mapping", static_cast<int>(LFOmappings.size()));
                        // Close LFO Mappings itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 4);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        // ADD LEVEL TWO
                        int newIndent = choices[highlight].indentLevel;
                        addLevelTwo(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                
// L E V E L  T W O -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -
                
                // EFFECTS
                if (choices[highlight].name == "  Distortion") {
                    if (choices[highlight].isOpen) {
                        // Close Level Three
                        closeMenu(choices, "    Display Distortion Settings", 2);
                        // Close Distortion itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 4);  // # + 1
                        choices[highlight].isOpen = false;  // Mark as closed
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;   // Mark as open
                    }
                }
                if (choices[highlight].name == "  Flanger") {
                    if (choices[highlight].isOpen) {
                        // Close Level Three
                        closeMenu(choices, "    Display Flanger Settings", 2);
                        // Close Flanger itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 4);  // # + 1
                        choices[highlight].isOpen = false;  // Mark as closed
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;   // Mark as open
                    }
                }
                if (choices[highlight].name == "  Phaser") {
                    if (choices[highlight].isOpen) {
                        // Close Level Three
                        closeMenu(choices, "    Display Phaser Settings", 2);
                        // Close Phaser itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 4);  // # + 1
                        choices[highlight].isOpen = false;  // Mark as closed
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;   // Mark as open
                    }
                }
                if (choices[highlight].name == "  Filter") {
                    if (choices[highlight].isOpen) {
                        // Close Level Three
                        closeMenu(choices, "    Display Filter Settings", 2);
                        closeMenu(choices, "    Edit Lowpass Frequency", 1);
                        closeMenu(choices, "    Edit Lowpass Slope", 1);
                        // Close Filter itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 4);  // # + 1
                        choices[highlight].isOpen = false;  // Mark as closed
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;   // Mark as open
                    }
                }
                if (choices[highlight].name == "  Echo") {
                    if (choices[highlight].isOpen) {
                        // Close Level Three
                        closeMenu(choices, "    Display Echo Settings", 2);
                        // Close Echo itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 4);  // # + 1
                        choices[highlight].isOpen = false;  // Mark as closed
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;   // Mark as open
                    }
                }
                if (choices[highlight].name == "  Reverb") {
                    if (choices[highlight].isOpen) {
                        // Close Level Three
                        closeMenu(choices, "    Display Reverb Settings", 2);
                        // Close Reverb itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 4);  // # + 1
                        choices[highlight].isOpen = false;  // Mark as closed
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;   // Mark as open
                    }
                }
                
                // Synthesizer Mode
                if (choices[highlight].name == "  Choose Waveform") {
                    if (choices[highlight].isOpen) {
                        // CURRENTLY OPEN
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 7);  // # + 1
                        choices[highlight].isOpen = false;  // Mark as closed
                    } else {
                        // CURRENTLY CLOSED
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;   // Mark as open
                    }
                }
                
                // PRESETS
                if (choices[highlight].name == "  Save as Preset") {
                    createPreset();
                }
                
                if (choices[highlight].name == "  View Presets") {
                    // Incase a heathen deletes from initialized vector
                    if (usrPresets.empty()) usrPresets.push_back("    Really?");
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + usrPresets.size() + 1);
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;
                    }
                }
                
                if (choices[highlight].name == "  Delete Preset")
                {
                    // Incase a heathen deletes from initialized vector
                    if (usrPresets.empty()) usrPresets.push_back("    Really?");
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + usrPresets.size() + 1);
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;
                    }
                }
                // Ensure deletion only happens when "Delete Preset" is open
                bool deletePresetMode = false;
                for (const auto& choice : choices) {
                    if (choice.name == "  Delete Preset" && choice.isOpen) {
                        deletePresetMode = true;
                        break;
                    }
                }
                if (deletePresetMode) {
                    for (size_t i = 0; i < usrPresets.size(); ++i) {
                        if (choices[highlight].name == usrPresets[i]) {
                            // Remove from usrPresets
                            usrPresets.erase(usrPresets.begin() + i);
                            
                            // Remove from choices
                            choices.erase(choices.begin() + highlight);
                            highlight = max(0, highlight - 1); // Prevent out-of-bounds issues
                            break;
                        }
                    }
                }
                
                // RECORD SAMPLE
                if (choices[highlight].name == "  Record Sample") {
                    // Record Audio. Also toggled by global button
                }
                
                // CHOOSE SAMPLE
                if (choices[highlight].name == "  Choose Sample") {
                    if (choices[highlight].isOpen) {
                        // CLOSE LEVEL FIVE
                        closeMenu(choices, "      Arps", 5);
                        closeMenu(choices, "      Basses", 20);
                        closeMenu(choices, "      Leads", 8);
                        closeMenu(choices, "      Pads", 8);
                        closeMenu(choices, "      Brass", 5);
                        closeMenu(choices, "      Choir", 5);
                        closeMenu(choices, "      Strings", 5);
                        closeMenu(choices, "      Harp", 4);
                        closeMenu(choices, "      Guitar", 5);
                        closeMenu(choices, "      Kicks", 10);
                        closeMenu(choices, "      Snares", 10);
                        closeMenu(choices, "      Claps", 3);
                        closeMenu(choices, "      Crashes", 3);
                        closeMenu(choices, "      HiHats", 5);
                        closeMenu(choices, "      Rides", 5);
                        closeMenu(choices, "      Toms", 5);
                        closeMenu(choices, "      Other", 5);
                        // CLOSE LEVEL FOUR
                        closeMenu(choices, "    Synths", 4);
                        closeMenu(choices, "    Instruments", 5);
                        closeMenu(choices, "    Drums", 8);
                        closeMenu(choices, "    Misc.", 18);
                        // Close Choose Sample itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 5);  // # + 1
                        choices[highlight].isOpen = false;
                    } else {
                        // CURRENTLY CLOSED
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                
                // SONG BUILDER
                if (choices[highlight].name ==  "  New Song")
                {
               
                    
                    
                }
                if (choices[highlight].name ==   "  Load Song")
                {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + usrSongs.size() + 1);  // # + 1
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                if (choices[highlight].name == "  Record Sequence")
                {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 2);  // # + 1
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        createSequence(); // Will need to edit what this actually does later
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                if (choices[highlight].name == "  Delete Sequence")
                {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + usrTakes.size() + 1);  // # + 1
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                // Ensure deletion only happens when "Delete Sequence" is open
                bool deleteTakeMode = false;
                for (const auto& choice : choices) {
                    if (choice.name == "  Delete Sequence" && choice.isOpen) {
                        deleteTakeMode = true;
                        break;
                    }
                }
                if (deleteTakeMode) {
                    for (size_t i = 0; i < usrTakes.size(); ++i) {
                        if (choices[highlight].name == usrTakes[i]) {
                            // Remove from usrPresets
                            usrTakes.erase(usrTakes.begin() + i);
                            // Remove from choices
                            choices.erase(choices.begin() + highlight);
                            highlight = max(0, highlight - 1); // Prevent out-of-bounds issues
                            break;
                        }
                    }
                }
                if (choices[highlight].name == "  Delete Song")
                {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + usrSongs.size() + 1);  // # + 1
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                // Ensure deletion only happens when "Delete Song" is open
                bool deleteSongMode = false;
                for (const auto& choice : choices) {
                    if (choice.name == "  Delete Song" && choice.isOpen) {
                        deleteSongMode = true;
                        break;
                    }
                }
                if (deleteSongMode) {
                    for (size_t i = 0; i < usrSongs.size(); ++i) {
                        if (choices[highlight].name == usrSongs[i]) {
                            // Remove from usrPresets
                            usrSongs.erase(usrSongs.begin() + i);
                            // Remove from choices
                            choices.erase(choices.begin() + highlight);
                            highlight = max(0, highlight - 1); // Prevent out-of-bounds issues
                            break;
                        }
                    }
                }
                
                
                // LFOs
                if (choices[highlight].name == "  Create LFO")
                {
                    createLFO();
                }
                if (choices[highlight].name == "  Display Mappings")
                {
                    // Incase a heathen deletes from initialized vector
                    if (LFOmappings.empty()) {
                        LFOmappings.push_back("    Really?");
                    }
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + LFOmappings.size() + 1); // # + 1
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                if (choices[highlight].name == "  Remove Mapping")
                {
                    // Incase a heathen deletes from initialized vector
                    if (LFOmappings.empty()) {
                        LFOmappings.push_back("    Really?");
                    }
                    
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + LFOmappings.size() + 1);
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;
                    }
                }
                // Ensure deletion only happens when "Delete LFO" is open
                bool deleteLFOMode = false;
                for (const auto& choice : choices) {
                    if (choice.name == "  Remove Mapping" && choice.isOpen) {
                        deleteLFOMode = true;
                        break;
                    }
                }
                if (deleteLFOMode) {
                    for (size_t i = 0; i < LFOmappings.size(); ++i) {
                        if (choices[highlight].name == LFOmappings[i]) {
                            // Remove from usrPresets
                            LFOmappings.erase(LFOmappings.begin() + i);
                            // Remove from choices
                            choices.erase(choices.begin() + highlight);
                            highlight = max(0, highlight - 1); // Prevent out-of-bounds issues
                            break;
                        }
                    }
                }
                
// L E V E L  T H R E E --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
                
                // Distortion
                if (choices[highlight].name == "    Display Distortion Settings") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 3);  // # + 1
                        choices[highlight].isOpen = false;  // Mark as closed
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);
                        choices[highlight].isOpen = true;   // Mark as open
                    }
                }
                // Flanger
                if (choices[highlight].name == "    Display Flanger Settings") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 3);  // # + 1
                        choices[highlight].isOpen = false;  // Mark as closed
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);
                        choices[highlight].isOpen = true;   // Mark as open
                    }
                }
                // Phaser
                if (choices[highlight].name == "    Display Phaser Settings") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 3);  // # + 1
                        choices[highlight].isOpen = false;  // Mark as closed
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);
                        choices[highlight].isOpen = true;   // Mark as open
                    }
                }
                // FILTER
                if (choices[highlight].name == "    Display Filter Settings") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 3);  // # + 1
                        choices[highlight].isOpen = false;  // Mark as closed
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);
                        choices[highlight].isOpen = true;   // Mark as open
                    }
                }
                if (choices[highlight].name == "    Edit Lowpass Frequency") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 3);  // # + 1
                        choices[highlight].isOpen = false;  // Mark as closed
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);
                        choices[highlight].isOpen = true;   // Mark as open
                        
                        // Activate UpDown Mode
                        ChangeLowpassFrequency(KNOB_FltLP, menuWindow);
                    }
                }
                if (choices[highlight].name == "    Edit Lowpass Slope") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 3);  // # + 1
                        choices[highlight].isOpen = false;  // Mark as closed
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);
                        choices[highlight].isOpen = true;   // Mark as open
                        
                        // Activate UpDown Mode
                        ChangeLowpassSlope(KNOB_FltQ, menuWindow);
                    }
                }
                // Echo
                if (choices[highlight].name == "    Display Echo Settings") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 3);  // # + 1
                        choices[highlight].isOpen = false;  // Mark as closed
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);
                        choices[highlight].isOpen = true;   // Mark as open
                    }
                }
                // Reverb
                if (choices[highlight].name == "    Display Reverb Settings") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 3);  // # + 1
                        choices[highlight].isOpen = false;  // Mark as closed
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);
                        choices[highlight].isOpen = true;   // Mark as open
                    }
                }
                
                // Choose Waveform
                if (choices[highlight].name == "    Saw")
                {
                    currentWaveType = WaveType::SAW;                  // Set globally chosen WaveType
                    OscEngine(currentWaveType);                       // Generate waveform
                    setCurrSample("OscillatorWaveform_9");            // Set current sample
                    playCurrentSample("OscillatorWaveform_9");   // Play the sample
                }
                
                if (choices[highlight].name == "    Square")
                {
                    currentWaveType = WaveType::SQUARE;               // Set globally chosen WaveType
                    OscEngine(currentWaveType);                       // Generate waveform
                    setCurrSample("OscillatorWaveform_9");            // Set current sample
                    playCurrentSample("OscillatorWaveform_9");   // Play the sample
                }
                
                if (choices[highlight].name == "    Sine")
                {
                    currentWaveType = WaveType::SINE;                 // Set globally chosen WaveType
                    OscEngine(currentWaveType);                       // Generate waveform
                    setCurrSample("OscillatorWaveform_9");            // Set current sample
                    playCurrentSample("OscillatorWaveform_9");   // Play the sample
                }
                
                if (choices[highlight].name == "    Glorkglunk")
                {
                    currentWaveType = WaveType::GLORKGLUNK;           // Set globally chosen WaveType
                    OscEngine(currentWaveType);                       // Generate waveform
                    setCurrSample("OscillatorWaveform_9");            // Set current sample
                    playCurrentSample("OscillatorWaveform_9");   // Play the sample
                }
                
                if (choices[highlight].name == "    Drum Fill")
                {
                    currentWaveType = WaveType::DRUMFILL;             // Set globally chosen WaveType
                    OscEngine(currentWaveType);                       // Generate waveform
                    setCurrSample("OscillatorWaveform_9");            // Set current sample
                    playCurrentSample("OscillatorWaveform_9");   // Play the sample
                }
                
                if (choices[highlight].name == "    Dune")
                {
                    currentWaveType = WaveType::DUNE;                 // Set globally chosen WaveType
                    OscEngine(currentWaveType);                       // Generate waveform
                    setCurrSample("OscillatorWaveform_9");            // Set current sample
                    playCurrentSample("OscillatorWaveform_9");   // Play the sample
                }
                
                // Choose Sample
                // SYNTHS------------------------------------------------------
                if (choices[highlight].name == "    Synths") {
                    if (choices[highlight].isOpen) {
                        // CLOSE LEVEL FIVE
                        closeMenu(choices, "      Arps", 5);
                        closeMenu(choices, "      Basses", 20);
                        closeMenu(choices, "      Leads", 8);
                        closeMenu(choices, "      Pads", 8);
                        // Close Synths itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 5);
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);
                        choices[highlight].isOpen = true;
                    }
                }
                
                // INSTRUMENTS-------------------------------------------------
                if (choices[highlight].name == "    Instruments") {
                    if (choices[highlight].isOpen) {
                        // CLOSE LEVEL 5
                        closeMenu(choices, "      Brass", 5);
                        closeMenu(choices, "      Choir", 5);
                        closeMenu(choices, "      Strings", 5);
                        closeMenu(choices, "      Harp", 4);
                        closeMenu(choices, "      Guitar", 5);
                        // Close Instruments itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 6);
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                
                // DRUMS-------------------------------------------------------
                if (choices[highlight].name == "    Drums") {
                    if (choices[highlight].isOpen) {
                        // CLOSE LEVEL 5
                        closeMenu(choices, "      Kicks", 10);
                        closeMenu(choices, "      Snares", 10);
                        closeMenu(choices, "      Claps", 3);
                        closeMenu(choices, "      Crashes", 3);
                        closeMenu(choices, "      HiHats", 5);
                        closeMenu(choices, "      Rides", 5);
                        closeMenu(choices, "      Toms", 5);
                        closeMenu(choices, "      Other", 5);
                        // Close Drums itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 9);
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);
                        choices[highlight].isOpen = true;
                    }
                }
                
                // MISC.-------------------------------------------------------
                if (choices[highlight].name == "    Misc.") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 19);  // + 1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                
                // L E V E L  F O U R ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- --
                
                // SAMPLE LIBRARY----------------------------------------------
                vector<string> menuNames = {
                    "      Arps", "      Basses", "      Leads", "      Pads",
                    "      Brass", "      Choir", "      Strings", "      Harp", "      Guitar",
                    "      Kicks", "      Snares", "      Claps", "      Crashes",
                    "      HiHats", "      Rides", "      Toms", "      Other"
                };
                vector<int> menuOptions = {
                    5, 20, 8, 8,
                    5, 5, 5, 4, 5,
                    10, 10, 3, 3,
                    5, 5, 5, 5
                };
                for (size_t i = 0; i < menuNames.size(); ++i) {
                    if (choices[highlight].name == menuNames[i]) {
                        if (choices[highlight].isOpen) {
                            choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 1 + menuOptions[i]);
                            choices[highlight].isOpen = false;
                        } else {
                            int newIndent = choices[highlight].indentLevel;
                            addLevelFive(highlight, newIndent);
                            choices[highlight].isOpen = true;
                        }
                        break; // Exit the loop early once a match is found
                    }
                }
                
                // Misc.
                playAudioFromCategory(highlight, "Misc", 18);
                
                
// L E V E L  F I V E ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
                
                // P L A Y  A U D I O
                playAudioFromCategory(highlight, "Arp", 5);
                playAudioFromCategory(highlight, "Bass", 20);
                playAudioFromCategory(highlight, "Lead", 8);
                playAudioFromCategory(highlight, "Pad", 8);
                playAudioFromCategory(highlight, "Brass", 5);
                playAudioFromCategory(highlight, "Choir", 5);
                playAudioFromCategory(highlight, "Strings", 5);
                playAudioFromCategory(highlight, "Harp", 4);
                playAudioFromCategory(highlight, "Guitar", 5);
                playAudioFromCategory(highlight, "Kick", 10);
                playAudioFromCategory(highlight, "Snare", 10);
                playAudioFromCategory(highlight, "Clap", 3);
                playAudioFromCategory(highlight, "Crash", 3);
                playAudioFromCategory(highlight, "HiHat", 5);
                playAudioFromCategory(highlight, "Ride", 5);
                playAudioFromCategory(highlight, "Tom", 5);
                playAudioFromCategory(highlight, "Other", 5);
                
                // E X I T from L E V E L  O N E
                if (choices[highlight].name == "Exit")
                {
                    gpioTerminate();
                    cleanUpPresets();
                    atexit(cleanGeneratedFiles);
                    endwin();
                    exit(0);
                }
                break;
            }
        }
    }
    return 0;
}

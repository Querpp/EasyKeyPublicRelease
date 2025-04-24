/*******************************************************
 * File Name:    EasyKey v0.2.0
 *
 * Description:
 * - Entire system rewritten from scratch
 * - Higher-level menus close submenus
 * - Sample audio playback
 *
 * Author:       Ethan Laptew
 * Created:      2025-03-07
 * Version:      v0.2.0
 * License:      Public Domain / No Rights Reserved
 ********************************************************/

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <thread>
#include <vector>
using namespace std;

#include "audioPlayer.h"

struct MenuItem
{
    bool hasMiniSubs;           // Flag to track if the submenu already has minisubs
    bool isMiniSub;             // Flag to indicate if this is a minisub option
    bool isOpen;                // To track if the submenu is open (has sub-items)
    int indentLevel;
    string name;
    
    // Constructor for MenuItem
    MenuItem(const string& n, int i, bool minisub = false, bool has_subs = false, bool open = false)
    : name(n), indentLevel(i), isMiniSub(minisub), hasMiniSubs(has_subs), isOpen(open) {}
};

// Initialize menu with predefined options and sub-options
vector<MenuItem> choices;


//-------------------------------------------------------------------------------------------------
// FUNCTIONS

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

// LEVEL ONE - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void addLevelOne()
{
    choices.push_back(MenuItem("Presets", 0));
    choices.push_back(MenuItem("Sample Library", 0));
    choices.push_back(MenuItem("Song Builder", 0));
    choices.push_back(MenuItem("LFO Mappings", 0));
    choices.push_back(MenuItem("Exit", 0));
}

// LEVEL TWO -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
void addLevelTwo(int startIndex, int subIndent) {
    if (choices[startIndex].name == "Presets") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    View Presets", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    Save as Preset", subIndent));
    }
    if (choices[startIndex].name == "Sample Library") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Synths", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    Instruments", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("    Drums", subIndent));
        choices.insert(choices.begin() + startIndex + 4, MenuItem("    Misc.", subIndent));
    }
    if (choices[startIndex].name == "Song Builder") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Record Take", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    Delete Take", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("    View Songs",  subIndent));
    }
    if (choices[startIndex].name == "LFO Mappings") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Display Mappings", subIndent));
    }
}

// LEVEL THREE --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
void addLevelThree(int startIndex, int subIndent)
{
    // Presets
    if (choices[startIndex].name == "    View Presets") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("      List Presets", subIndent, true));
    }
    if (choices[startIndex].name == "    Save as Preset") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("      Save as..", subIndent, true));
    }
    
    // Sample Library
    if (choices[startIndex].name == "    Synths") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("      Arps", subIndent, true));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("      Basses", subIndent, true));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("      Leads", subIndent, true));
        choices.insert(choices.begin() + startIndex + 4, MenuItem("      Pads", subIndent, true));
    }
    if (choices[startIndex].name == "    Instruments") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("      Brass", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("      Choir", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("      Strings", subIndent));
        choices.insert(choices.begin() + startIndex + 4, MenuItem("      Harp", subIndent));
        choices.insert(choices.begin() + startIndex + 5, MenuItem("      Guitar", subIndent));
    }
    if (choices[startIndex].name == "    Drums") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("      Kicks", subIndent, true));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("      Snares", subIndent, true));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("      Claps", subIndent, true));
        choices.insert(choices.begin() + startIndex + 4, MenuItem("      Crashes", subIndent, true));
        choices.insert(choices.begin() + startIndex + 5, MenuItem("      HiHats", subIndent, true));
        choices.insert(choices.begin() + startIndex + 6, MenuItem("      Rides", subIndent, true));
        choices.insert(choices.begin() + startIndex + 7, MenuItem("      Toms", subIndent, true));
        choices.insert(choices.begin() + startIndex + 8, MenuItem("      Other", subIndent, true));
    }
    if (choices[startIndex].name == "    Misc.") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("      Misc 1", subIndent, true));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("      Misc 2", subIndent, true));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("      Misc 3", subIndent, true));
        choices.insert(choices.begin() + startIndex + 4, MenuItem("      Misc 4", subIndent, true));
        choices.insert(choices.begin() + startIndex + 5, MenuItem("      Misc 5", subIndent, true));
        choices.insert(choices.begin() + startIndex + 6, MenuItem("      Misc 6", subIndent, true));
        choices.insert(choices.begin() + startIndex + 7, MenuItem("      Misc 7", subIndent, true));
        choices.insert(choices.begin() + startIndex + 8, MenuItem("      Misc 8", subIndent, true));
        choices.insert(choices.begin() + startIndex + 9, MenuItem("      Misc 9", subIndent, true));
        choices.insert(choices.begin() + startIndex + 10, MenuItem("      Misc 10", subIndent, true));
        choices.insert(choices.begin() + startIndex + 11, MenuItem("      Misc 11", subIndent, true));
        choices.insert(choices.begin() + startIndex + 12, MenuItem("      Misc 12", subIndent, true));
        choices.insert(choices.begin() + startIndex + 13, MenuItem("      Misc 13", subIndent, true));
        choices.insert(choices.begin() + startIndex + 14, MenuItem("      Misc 14", subIndent, true));
        choices.insert(choices.begin() + startIndex + 15, MenuItem("      Misc 15", subIndent, true));
        choices.insert(choices.begin() + startIndex + 16, MenuItem("      Misc 16", subIndent, true));
        choices.insert(choices.begin() + startIndex + 17, MenuItem("      Misc 17", subIndent, true));
        choices.insert(choices.begin() + startIndex + 18, MenuItem("      Misc 18", subIndent, true));
        choices.insert(choices.begin() + startIndex + 19, MenuItem("      Misc 19", subIndent, true));
    }
    
    // Song Builder
    if (choices[startIndex].name == "    Delete Take") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("      Select Take", subIndent, true));
    }
}

// L E V E L  F O U R ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- --
void addLevelFour(int startIndex, int subIndent)
{
    // SYNTHS
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
    
    // INSTRUMENTS
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
    
    // DRUMS
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


//-----------------------------------------------------------------------------------------------------------------------------------------

int main()
{
    clearScreen();
    ncursesInitialize();
    openingAnimation();
    
    // Create Menu Window
    int height = 20, width = 50, startY = 1, startX = 1;
    WINDOW* menuWindow = newwin(height, width, startY, startX);
    box(menuWindow, 0, 0);
    int highlight = 0, choice = 0, scrollOffset = 0;
    keypad(menuWindow, TRUE);
    
    addLevelOne();
    
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
        wrefresh(menuWindow);
        choice = wgetch(menuWindow);
        
        switch(choice) {
            case KEY_UP:
                (highlight > 0) ? highlight-- : highlight;
                (highlight < scrollOffset) ? --scrollOffset : scrollOffset;
                break;
            case KEY_DOWN:
                (highlight < choices.size() - 1) ? highlight++ : highlight;
                (highlight >= scrollOffset + height -2) ? scrollOffset++ : scrollOffset;
                break;
                
            case 10: {
                // L E V E L  O N E - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                // Choice == PRESETS
                if (choices[highlight].name == "Presets") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 3);  // # + 1
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelTwo(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                
                // Choice == SAMPLE LIBRARY
                else if (choices[highlight].name == "Sample Library")
                {
                    // CURRENTLY OPEN
                    if (choices[highlight].isOpen)
                    {
                        // CLOSE LEVEL FOUR
                        vector<pair<string, int>> categories = {
                            {"      Arps", 7}, {"      Basses", 23}, {"      Leads", 8}, {"      Pads", 8},
                            {"      Brass", 5}, {"      Choir", 5}, {"      Strings", 5}, {"      Harp", 4},
                            {"      Guitar", 5}, {"      Kicks", 10}, {"      Snares", 12}, {"      Claps", 3},
                            {"      Crashes", 3}, {"      HiHats", 6}, {"      Rides", 5}, {"      Toms", 5},
                            {"      Other", 7}
                        };
                        for (const auto& category : categories) {
                            for (int i = 0; i < choices.size(); ++i) {
                                if (choices[i].name == category.first && choices[i].isOpen) {
                                    int numOptions = category.second;
                                    choices.erase(choices.begin() + i + 1, choices.begin() + i + numOptions + 1);
                                    choices[i].isOpen = false;  // Mark as closed
                                }
                            }
                        }
                        // CLOSE LEVEL THREE
                        vector<pair<string, int>> levelThreeCategories = {
                            {"    Misc.", 19}, {"    Synths", 4}, {"    Instruments", 5}, {"    Drums", 8}
                        };
                        for (const auto& category : levelThreeCategories) {
                            for (int i = 0; i < choices.size(); ++i) {
                                if (choices[i].name == category.first && choices[i].isOpen) {
                                    int numOptions = category.second;
                                    choices.erase(choices.begin() + i + 1, choices.begin() + i + numOptions + 1);
                                    choices[i].isOpen = false;  // Mark as closed
                                }
                            }
                        }
                        // Close Sample Library itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 5);  // 4 options
                        choices[highlight].isOpen = false;
                    }
                    // CURRENTLY CLOSED
                    else
                    {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelTwo(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                
                
                
                // Choice == SONG BUILDER
                else if (choices[highlight].name == "Song Builder") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 4);  // +1 number of sub options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelTwo(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                
                // Choice == LFO MAPPINGS
                else if (choices[highlight].name == "LFO Mappings") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 2);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelTwo(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                
                // L E V E L  T W O -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -
                // SYNTHS------------------------------------------------------
                if (choices[highlight].name == "    Synths") {
                    // CURRENTLY OPEN
                    if (choices[highlight].isOpen) {
                        // Define category names and their associated number of options
                        vector<string> categoryNames = {
                            "      Arps", "      Basses", "      Leads", "      Pads"
                        };
                        vector<int> categoryOptions = {
                            7, 23, 8, 8
                        };
                        // Loop through the categories and close them
                        for (size_t i = 0; i < categoryNames.size(); ++i) {
                            for (int j = 0; j < choices.size(); ++j) {
                                if (choices[j].name == categoryNames[i] && choices[j].isOpen) {
                                    int numOptions = categoryOptions[i];
                                    choices.erase(choices.begin() + j + 1, choices.begin() + j + numOptions + 1);
                                    choices[j].isOpen = false;
                                }
                            }
                        }
                        // Close Synths itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 5);
                        choices[highlight].isOpen = false;
                    } else {
                        // CURRENTLY CLOSED
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;
                    }
                }
                
                // INSTRUMENTS-------------------------------------------------
                else if (choices[highlight].name == "    Instruments") {
                    // CURRENTLY OPEN
                    if (choices[highlight].isOpen) {
                        // Define category names and their associated number of options
                        vector<string> categoryNames = {
                            "      Brass", "      Choir",
                            "      Strings", "      Harp", "      Guitar"
                        };
                        vector<int> categoryOptions = {
                            5, 5, 5, 4, 5
                        };
                        
                        // Loop through the categories and close them
                        for (size_t i = 0; i < categoryNames.size(); ++i) {
                            for (int j = 0; j < choices.size(); ++j) {
                                if (choices[j].name == categoryNames[i] && choices[j].isOpen) {
                                    int numOptions = categoryOptions[i];
                                    choices.erase(choices.begin() + j + 1, choices.begin() + j + numOptions + 1);
                                    choices[j].isOpen = false;
                                }
                            }
                        }
                        // Close Instruments itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 6);
                        choices[highlight].isOpen = false;
                    } else {
                        // CURRENTLY CLOSED
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                
                // DRUMS-------------------------------------------------------
                else if (choices[highlight].name == "    Drums") {
                    // CURRENTLY OPEN
                    if (choices[highlight].isOpen) {
                        // Define category names and their associated number of options
                        vector<string> categoryNames = {
                            "      Kicks", "      Snares", "      Claps",
                            "      Crashes", "      HiHats", "      Rides", "      Toms", "      Other"
                        };
                        vector<int> categoryOptions = {
                            10, 12, 3, 3, 6, 5, 5, 7
                        };
                        // Loop through the categories and close them
                        for (size_t i = 0; i < categoryNames.size(); ++i) {
                            for (int j = 0; j < choices.size(); ++j) {
                                if (choices[j].name == categoryNames[i] && choices[j].isOpen) {
                                    int numOptions = categoryOptions[i];
                                    choices.erase(choices.begin() + j + 1, choices.begin() + j + numOptions + 1);
                                    choices[j].isOpen = false;
                                }
                            }
                        }
                        // Close Drums itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 9);
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;
                    }
                }
                
                // MISC.
                else if (choices[highlight].name == "    Misc.") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 20);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                
                
                // L E V E L  F O U R ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- --
                // SYNTH OPTIONS
                // Arps
                if (choices[highlight].name == "      Arps") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 8);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);                 // What level to open
                        choices[highlight].isOpen = true;                   // Mark as open
                    }
                }
                // Basses
                if (choices[highlight].name == "      Basses") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 24);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);                 // What level to open
                        choices[highlight].isOpen = true;                   // Mark as open
                    }
                }
                // Leads
                if (choices[highlight].name == "      Leads") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 9);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);                 // What level to open
                        choices[highlight].isOpen = true;                   // Mark as open
                    }
                }
                // Pads
                if (choices[highlight].name == "      Pads") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 9);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);                 // What level to open
                        choices[highlight].isOpen = true;                   // Mark as open
                    }
                }
                
                // INSTRUMENT OPTIONS
                // Brass
                if (choices[highlight].name == "      Brass") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 6);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);                 // What level to open
                        choices[highlight].isOpen = true;                   // Mark as open
                    }
                }
                // Choir
                if (choices[highlight].name == "      Choir") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 6);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);                 // What level to open
                        choices[highlight].isOpen = true;                   // Mark as open
                    }
                }
                // Strings
                if (choices[highlight].name == "      Strings") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 6);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);                 // What level to open
                        choices[highlight].isOpen = true;                   // Mark as open
                    }
                }
                // Harp
                if (choices[highlight].name == "      Harp") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 5);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);                 // What level to open
                        choices[highlight].isOpen = true;                   // Mark as open
                    }
                }
                // Guitar
                if (choices[highlight].name == "      Guitar") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 6);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);                 // What level to open
                        choices[highlight].isOpen = true;                   // Mark as open
                    }
                }
                
                // DRUM OPTIONS
                // Kicks
                if (choices[highlight].name == "      Kicks") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 11);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);                 // What level to open
                        choices[highlight].isOpen = true;                   // Mark as open
                    }
                }
                // Snares
                if (choices[highlight].name == "      Snares") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 13);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);                 // What level to open
                        choices[highlight].isOpen = true;                   // Mark as open
                    }
                }
                // Claps
                if (choices[highlight].name == "      Claps") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 4);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);                 // What level to open
                        choices[highlight].isOpen = true;                   // Mark as open
                    }
                }
                // Crashes
                if (choices[highlight].name == "      Crashes") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 4);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);                 // What level to open
                        choices[highlight].isOpen = true;                   // Mark as open
                    }
                }
                // HiHats
                if (choices[highlight].name == "      HiHats") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 7);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);                 // What level to open
                        choices[highlight].isOpen = true;                   // Mark as open
                    }
                }
                // Rides
                if (choices[highlight].name == "      Rides") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 6);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);                 // What level to open
                        choices[highlight].isOpen = true;                   // Mark as open
                    }
                }
                // Toms
                if (choices[highlight].name == "      Toms") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 6);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);                 // What level to open
                        choices[highlight].isOpen = true;                   // Mark as open
                    }
                }
                // Other
                if (choices[highlight].name == "      Other") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 8);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);                 // What level to open
                        choices[highlight].isOpen = true;                   // Mark as open
                    }
                }
                
                // Arps
                for (int i = 1; i <= 7; ++i) {
                    string arpName = "        Arp_" + to_string(i);
                    if (choices[highlight].name == arpName) {
                        filePath(arpName);
                        break;  // Exit loop once the match is found
                    }
                }
                // Basses
                for (int i = 1; i <= 23; ++i) {
                    string bassName = "        Bass_" + to_string(i);
                    if (choices[highlight].name == bassName) {
                        filePath(bassName);
                        break;  // Exit loop once the match is found
                    }
                }
                // Leads
                for (int i = 1; i <= 8; ++i) {
                    string leadName = "        Lead_" + to_string(i);
                    if (choices[highlight].name == leadName) {
                        filePath(leadName);
                        break;  // Exit loop once the match is found
                    }
                }
                // Pads
                for (int i = 1; i <= 8; ++i) {
                    string padName = "        Bass_" + to_string(i);
                    if (choices[highlight].name == padName) {
                        filePath(padName);
                        break;  // Exit loop once the match is found
                    }
                }
                // Brass
                for (int i = 1; i <= 5; ++i) {
                    string brassName = "        Brass_" + to_string(i);
                    if (choices[highlight].name == brassName) {
                        filePath(brassName);
                        break;  // Exit loop once the match is found
                    }
                }
                // Choir
                for (int i = 1; i <= 5; ++i) {
                    string choirName = "        Choir_" + to_string(i);
                    if (choices[highlight].name == choirName) {
                        filePath(choirName);
                        break;  // Exit loop once the match is found
                    }
                }
                // Strings
                for (int i = 1; i <= 5; ++i) {
                    string stringName = "        String_" + to_string(i);
                    if (choices[highlight].name == stringName) {
                        filePath(stringName);
                        break;  // Exit loop once the match is found
                    }
                }
                // Harps
                for (int i = 1; i <= 4; ++i) {
                    string harpName = "        Harp_" + to_string(i);
                    if (choices[highlight].name == harpName) {
                        filePath(harpName);
                        break;  // Exit loop once the match is found
                    }
                }
                // Guitar
                for (int i = 1; i <= 5; ++i) {
                    string guitarName = "        Guitar_" + to_string(i);
                    if (choices[highlight].name == guitarName) {
                        filePath(guitarName);
                        break;  // Exit loop once the match is found
                    }
                }
                // Kicks
                for (int i = 1; i <= 10; ++i) {
                    string kickName = "        Kick_" + to_string(i);
                    if (choices[highlight].name == kickName) {
                        filePath(kickName);
                        break;  // Exit loop once the match is found
                    }
                }
                // Snares
                for (int i = 1; i <= 12; ++i) {
                    string snareName = "        Snare_" + to_string(i);
                    if (choices[highlight].name == snareName) {
                        filePath(snareName);
                        break;  // Exit loop once the match is found
                    }
                }
                // Claps
                for (int i = 1; i <= 3; ++i) {
                    string clapName = "        Clap_" + to_string(i);
                    if (choices[highlight].name == clapName) {
                        filePath(clapName);
                        break;  // Exit loop once the match is found
                    }
                }
                // Crashes
                for (int i = 1; i <= 3; ++i) {
                    string crashName = "        Crash_" + to_string(i);
                    if (choices[highlight].name == crashName) {
                        filePath(crashName);
                        break;  // Exit loop once the match is found
                    }
                }
                // HiHats
                for (int i = 1; i <= 6; ++i) {
                    string hiHatName = "        HiHat_" + to_string(i);
                    if (choices[highlight].name == hiHatName) {
                        filePath(hiHatName);
                        break;  // Exit loop once the match is found
                    }
                }
                // Rides
                for (int i = 1; i <= 5; ++i) {
                    string rideName = "        Ride_" + to_string(i);
                    if (choices[highlight].name == rideName) {
                        filePath(rideName);
                        break;  // Exit loop once the match is found
                    }
                }
                // Toms
                for (int i = 1; i <= 5; ++i) {
                    string tomName = "        Tom_" + to_string(i);
                    if (choices[highlight].name == tomName) {
                        filePath(tomName);
                        break;  // Exit loop once the match is found
                    }
                }
                // Other
                for (int i = 1; i <= 7; ++i) {
                    string otherName = "        Other_" + to_string(i);
                    if (choices[highlight].name == otherName) {
                        filePath(otherName);
                        break;  // Exit loop once the match is found
                    }
                }
                
                
                if (choices[highlight].name == "Exit") {
                    endwin();
                    exit(0);
                }
                break;
            }
        }
    }
    return 0;
}

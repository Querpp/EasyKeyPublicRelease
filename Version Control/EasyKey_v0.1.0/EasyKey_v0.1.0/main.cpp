/***********************************************
 * File Name:    EasyKey v0.1.0
 * 
 * Description:
 * - Implements a basic menu system for the EasyKey project
 * - Includes functions for managing menu levels
 * - Known issues:
 *   - Submenus do not properly close lower levels
 *   - Various usability issues
 *
 * Author:       Ethan Laptew
 * Created:      2025-02-17
 * Version:      v0.1.0
 * License:     Public Domain / No Rights Reserved
 ********************************************************/

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>

using namespace std;

struct MenuItem {
    bool has_minisubs;       // Flag to track if the submenu already has minisubs
    bool is_minisub;         // Flag to indicate if this is a minisub option
    bool is_open;            // To track if the submenu is open (has sub-items)
    int indent_level;
    string name;
    
    // Constructor for MenuItem
    MenuItem(const string& n, int i, bool minisub = false, bool has_subs = false, bool open = false)
    : name(n), indent_level(i), is_minisub(minisub), has_minisubs(has_subs), is_open(open) {}
};

// Initialize menu with predefined options and sub-options
vector<MenuItem> choices;

// Function Declarations
void addMinisubOptions(int startIndex, int subIndent);
void addSubOptions(int startIndex, int subIndent);
void clearScreen();
void initializeMenu();
void removeMinisubOptions(int highlight);
void toggleMinisubMenus(int highlight);

//---------------------------------------------------------------------------------------------------------------------
// FUNCTIONS

// Clear screen
void clearScreen() {
    cout << "\033[2J\033[H";
}


// LEVEL ONE - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void initializeMenu(){
    choices.push_back(MenuItem("Presets", 0));
    choices.push_back(MenuItem("Sample Library", 0));
    choices.push_back(MenuItem("Song Builder", 0));
    choices.push_back(MenuItem("LFO Mappings", 0));
    choices.push_back(MenuItem("Exit", 0));
}

// LEVEL TWO -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
void addSubOptions(int startIndex, int subIndent)
{
    if (choices[startIndex].name == "Presets") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("  View Presets", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("  Save as Preset", subIndent));
    }
    if (choices[startIndex].name == "Sample Library") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("  Synths", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("  Instruments", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("  Drums", subIndent));
        choices.insert(choices.begin() + startIndex + 4, MenuItem("  Misc.", subIndent));
    }
    if (choices[startIndex].name == "Song Builder") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("  Record Take", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("  Delete Take", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("  View Songs",  subIndent));
    }
    if (choices[startIndex].name == "LFO Mappings") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("  Display Mappings", subIndent));
    }
}


// LEVEL THREE --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
void addMinisubOptions(int startIndex, int subIndent)
{
    // Presets
    if (choices[startIndex].name == "  View Presets") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    List Presets", subIndent, true));
    }
    if (choices[startIndex].name == "  Save as Preset") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Save as..", subIndent, true));
    }
    
    // Sample Library
    if (choices[startIndex].name == "  Synths") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Arps", subIndent, true));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    Basses", subIndent, true));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("    Leads", subIndent, true));
        choices.insert(choices.begin() + startIndex + 4, MenuItem("    Pads", subIndent, true));
    }
    if (choices[startIndex].name == "  Instruments") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Brass", subIndent));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    Choir", subIndent));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("    Strings", subIndent));
        choices.insert(choices.begin() + startIndex + 4, MenuItem("    Harp", subIndent));
        choices.insert(choices.begin() + startIndex + 5, MenuItem("    Guitar", subIndent));
    }
    if (choices[startIndex].name == "  Drums") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Kicks", subIndent, true));
        choices.insert(choices.begin() + startIndex + 2, MenuItem("    Snares", subIndent, true));
        choices.insert(choices.begin() + startIndex + 3, MenuItem("    Claps", subIndent, true));
        choices.insert(choices.begin() + startIndex + 4, MenuItem("    Crashes", subIndent, true));
        choices.insert(choices.begin() + startIndex + 5, MenuItem("    HiHats", subIndent, true));
        choices.insert(choices.begin() + startIndex + 6, MenuItem("    Rides", subIndent, true));
        choices.insert(choices.begin() + startIndex + 7, MenuItem("    Toms", subIndent, true));
        choices.insert(choices.begin() + startIndex + 8, MenuItem("    Other", subIndent, true));
    }
    
    // Song Builder
    if (choices[startIndex].name == "  Delete Take") {
        choices.insert(choices.begin() + startIndex + 1, MenuItem("    Select Take", subIndent, true));
    }
}

//-------------------------------------------------------------------------------------------------
//*************************************************************************************************
//-------------------------------------------------------------------------------------------------

// Close LEVEL ONE
void removeMinisubOptions(int startIndex)
{
    // Presets
    if (choices[startIndex].name == "  View Presets") {
        choices.erase(choices.begin() + startIndex + 1, choices.begin() + startIndex + 2); // 1 options requires +2
    }
    if (choices[startIndex].name == "  Save as Preset") {
        choices.erase(choices.begin() + startIndex + 1, choices.begin() + startIndex + 2);
    }
    
    // Sample Library
    if (choices[startIndex].name == "  Synths") {
        choices.erase(choices.begin() + startIndex + 1, choices.begin() + startIndex + 5);  // 4 sub-options for Synths
    }
    if (choices[startIndex].name == "  Instruments") {
        choices.erase(choices.begin() + startIndex + 1, choices.begin() + startIndex + 6);  // 5 sub-options for Instruments
    }
    if (choices[startIndex].name == "  Drums") {
        choices.erase(choices.begin() + startIndex + 1, choices.begin() + startIndex + 9);  // 8 sub options for Drums
    }
    
    // Song Builder
    if (choices[startIndex].name == "  Record Take") {
        choices.erase(choices.begin() + startIndex + 1, choices.begin() + startIndex + 2);
    }
    if (choices[startIndex].name == "  Delete Take") {
        choices.erase(choices.begin() + startIndex + 1, choices.begin() + startIndex + 2);
    }
    
    // LFO Mappings
    if (choices[startIndex].name == "  Display Mappings") {
        choices.erase(choices.begin() + startIndex + 1, choices.begin() + startIndex + 10);
    }
}

// CLOSE SUB LEVEL (Any level)
void toggleMinisubMenus(int highlight) {
    int tempIndent = 2;
    
    // Handle "View Presets"
    if (choices[highlight].name == "  Presets") {
        if (!choices[highlight].is_open) {
            addMinisubOptions(highlight, tempIndent);
            choices[highlight].is_open = true;
        } else {
            removeMinisubOptions(highlight);
            choices[highlight].is_open = false;
        }
    }
    
    // Handle "View Presets"
    if (choices[highlight].name == "  View Presets") {
        if (!choices[highlight].is_open) {
            addMinisubOptions(highlight, tempIndent);
            choices[highlight].is_open = true;
        } else {
            removeMinisubOptions(highlight);
            choices[highlight].is_open = false;
        }
    }
    
    // Handle "Save as Preset"
    if (choices[highlight].name == "  Save as Preset") {
        if (!choices[highlight].is_open) {
            addMinisubOptions(highlight, tempIndent);
            choices[highlight].is_open = true;
        } else {
            removeMinisubOptions(highlight);
            choices[highlight].is_open = false;
        }
    }
    
    // Handle "Synths"
    if (choices[highlight].name == "  Synths") {
        if (!choices[highlight].is_open) {
            addMinisubOptions(highlight, tempIndent);
            choices[highlight].is_open = true;
        } else {
            removeMinisubOptions(highlight);  // Remove sub-options for "Synths"
            choices[highlight].is_open = false;
        }
    }
    
    // Handle "Instruments"
    if (choices[highlight].name == "  Instruments") {
        if (!choices[highlight].is_open) {
            // Add the sub-options if not open
            addMinisubOptions(highlight, tempIndent);
            choices[highlight].is_open = true; // Mark as open
        } else {
            removeMinisubOptions(highlight);
            choices[highlight].is_open = false; // Mark as closed
        }
    }
    
    // Handle "Drums"
    if (choices[highlight].name == "  Drums") {
        if (!choices[highlight].is_open) {
            addMinisubOptions(highlight, tempIndent);
            choices[highlight].is_open = true; // Mark as open
        } else {
            removeMinisubOptions(highlight);
            choices[highlight].is_open = false; // Mark as closed
        }
    }
    
    
    
    // Handle "Delete Take"
    if (choices[highlight].name == "  Delete Take") {
        if (!choices[highlight].is_open) {
            // Add the sub-options if not open
            addMinisubOptions(highlight, tempIndent);
            choices[highlight].is_open = true; // Mark as open
        } else {
            // Remove sub-options if open
            removeMinisubOptions(highlight);
            choices[highlight].is_open = false; // Mark as closed
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------

int main()
{
    clearScreen();
    
    // Opening animation
    const char* messages[] = {"Loading EasyKey   ", "Loading EasyKey.  ", "Loading EasyKey.. ", "Loading EasyKey..."};
    
    for (const char* msg : messages)
    {
        cout << "\r" << msg << flush;                       // Overwrite line
        this_thread::sleep_for(chrono::milliseconds(700));  // Pause length
    }
    cout << "\r          \r";                               // Clear line
    
    
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    // Create menu window
    int height = 12, width = 50, starty = 1, startx = 1;
    WINDOW* menuwin = newwin(height, width, starty, startx);
    box(menuwin, 0, 0);
    
    int highlight = 0;  // Track currently selected item
    int choice = 0;
    int scroll_offset = 0; // Scroll offset
    
    keypad(menuwin, TRUE);
    
    // Initialize menu items
    initializeMenu();
    
    while (true) {
        // Clear window and redraw the border
        wclear(menuwin);
        box(menuwin, 0, 0);
        
        // Calculate the maximum number of items that can be displayed
        int num_items_to_display = min(height - 2, (int)choices.size() - scroll_offset);
        
        // Display menu with scrolling
        for (int i = 0; i < num_items_to_display; i++)
        {
            int index = i + scroll_offset;
            if (index == highlight) {
                wattron(menuwin, A_REVERSE);
            }
            mvwprintw(menuwin, i + 1, choices[index].indent_level * 2 + 1, "%s", choices[index].name.c_str());
            wattroff(menuwin, A_REVERSE);
        }
        
        wrefresh(menuwin);
        choice = wgetch(menuwin);
        
        switch (choice) {
            case KEY_UP:
                if (highlight > 0) {
                    highlight--;
                }
                // If we're at the top of the menu, scroll the menu down
                if (highlight < scroll_offset) {
                    scroll_offset--;
                }
                break;
                
            case KEY_DOWN:
                if (highlight < choices.size() - 1) {
                    highlight++;
                }
                // If we're at the bottom of the visible area, scroll the menu up
                if (highlight >= scroll_offset + height - 2) {
                    scroll_offset++;
                }
                break;
                
            case 10: {
                //*************************************************************************************************
                // OPEN LEVEL ONE
                
                // Choice == PRESETS
                if (choices[highlight].name == "Presets") {
                    if (choices[highlight].is_open) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 3);  // 2 options
                        choices[highlight].is_open = false;
                    } else {
                        int newIndent = choices[highlight].indent_level + 1;
                        addSubOptions(highlight, newIndent);
                        choices[highlight].is_open = true;  // Mark as open
                    }
                }
                
                // Choice == SAMPLE LIBRARY
                else if (choices[highlight].name == "Sample Library") {
                    if (choices[highlight].is_open) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 5);  // 4 options
                        choices[highlight].is_open = false;
                    } else {
                        int newIndent = choices[highlight].indent_level + 1;
                        addSubOptions(highlight, newIndent);
                        choices[highlight].is_open = true;  // Mark as open
                    }
                }
                
                // Choice == SONG BUILDER
                else if (choices[highlight].name == "Song Builder") {
                    if (choices[highlight].is_open) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 4);  // +1 number of sub options
                        choices[highlight].is_open = false;
                    } else {
                        int newIndent = choices[highlight].indent_level + 1;
                        addSubOptions(highlight, newIndent);
                        choices[highlight].is_open = true;  // Mark as open
                    }
                }
                
                // Choice == LFO MAPPINGS
                else if (choices[highlight].name == "LFO Mappings") {
                    if (choices[highlight].is_open) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 2);  // +1 number of options
                        choices[highlight].is_open = false;
                    } else {
                        int newIndent = choices[highlight].indent_level + 1;
                        addSubOptions(highlight, newIndent);
                        choices[highlight].is_open = true;  // Mark as open
                    }
                }
                
                // Toggle LEVEL TWO
                else if (
                         choices[highlight].name == "  Presets" ||
                         // Presets
                         choices[highlight].name == "  View Presets" ||
                         choices[highlight].name == "  Save as Preset" ||
                         
                         // Sample Library
                         choices[highlight].name == "  Synths" ||
                         choices[highlight].name == "  Instruments" ||
                         choices[highlight].name == "  Drums" ||
                         
                         // Song Builder
                         choices[highlight].name == "  Record Take" ||
                         choices[highlight].name == "  Delete Take" ||
                         choices[highlight].name == "  View Songs" ||
                         
                         // LFO Mappings
                         choices[highlight].name == "  LFO Mappings")
                {
                    toggleMinisubMenus(highlight);
                }
                
                // CHOICE == EXIT
                else if (choices[highlight].name == "Exit") {
                    endwin();  // This is essential to clean up ncurses before exiting
                    exit(0);   // Exit the program
                }
                break;
            }
        }
    }
    return 0;
}

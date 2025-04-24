/*******************************************************
 * File Name:    EasyKey v0.3.0
 *
 * Description:
 * - v0.3.0 – Global Organization + Synth Sample Playback
 * - Synth partially implemented (uses pre-recorded audio)
 * - Introduced global variable `currentSample`
 * - Larger file structure with organized folders
 *
 * Author:       Ethan Laptew
 * Created:      2025-03-16
 * Version:      v0.3.0
 * License:      Public Domain / No Rights Reserved
 ********************************************************/

#include "AudioPlayer.h"
#include "GlobalVariables.h"
#include "KeyPress.h"
#include "MenuFunctions.h"

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

// Pick current sound
void updateSample(string newSample) {
    currentSample = newSample;
}


//---------------------------------------------------------------------------------------------------------------------

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
                
                // Handle the key press for 'a', 's', 'd', etc.
            case 'a':
                playCurrentSample(currentSample);
                break;
            case 's':
                playCurrentSample(currentSample);
                break;
            case 'd':
                playCurrentSample(currentSample);
                break;
            case 'f':
                playCurrentSample(currentSample);
                break;
            case 'g':
                playCurrentSample(currentSample);
                
            case 10: {
// L E V E L  O N E - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                // SYNTHESIZER MODE
                if (choices[highlight].name == "Synthesizer Mode") {
                    if (choices[highlight].isOpen) {
                        // CURRENTLY OPEN
                        // Close Level 2
                        for (int i = 0; i < choices.size(); ++i) {
                            if (choices[i].name == "  Choose Waveform" && choices[i].isOpen) {
                                int numOptions = 8;  // # options below current choice
                                choices.erase(choices.begin() + i + 1, choices.begin() + i + numOptions + 1); // Don't change this #
                                choices[i].isOpen = false;  // Mark as closed
                                break;
                            }
                        }
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
                if (choices[highlight].name == "Sampler Mode")
                {
                    // CURRENTLY OPEN
                    if (choices[highlight].isOpen)
                    {
                        // CLOSE LEVEL FIVE
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
                        // CLOSE LEVEL FOUR
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
                        // CLOSE LEVEL THREE
                        for (int i = 0; i < choices.size(); ++i) {
                            if (choices[i].name == "  Choose Sample" && choices[i].isOpen) {
                                int numOptions = 4;  // Number of level 4 options under Arps
                                choices.erase(choices.begin() + i + 1, choices.begin() + i + numOptions + 1);
                                choices[i].isOpen = false;  // Mark as closed
                                break;  // Stop after closing the Arps submenu
                            }
                        }
                        // Close Sampler Mode itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 3);  // # + 1
                        choices[highlight].isOpen = false;
                    }
                    // CURRENTLY CLOSED
                    else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelTwo(highlight, newIndent);  // Open level two if currently closed
                        choices[highlight].isOpen = true;
                    }
                }
                
                // Choice == PRESETS
                if (choices[highlight].name == "Presets") {
                    if (choices[highlight].isOpen) {
                        // Close Level Two
                        for (int i = 0; i < choices.size(); ++i) {
                            if (choices[i].name == "  View Presets" && choices[i].isOpen) {
                                int numOptions = 2;  // Number of level 4 options under Arps
                                choices.erase(choices.begin() + i + 1, choices.begin() + i + numOptions + 1);
                                choices[i].isOpen = false;  // Mark as closed
                                break;  // Stop after closing the Arps submenu
                            }
                        }
                        for (int i = 0; i < choices.size(); ++i) {
                            if (choices[i].name == "  Save as Preset" && choices[i].isOpen) {
                                int numOptions = 1;  // Number of level 4 options under Arps
                                choices.erase(choices.begin() + i + 1, choices.begin() + i + numOptions + 1);
                                choices[i].isOpen = false;  // Mark as closed
                                break;  // Stop after closing the Arps submenu
                            }
                        }
                        // Close Presets itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 3);  // # + 1
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
                        for (int i = 0; i < choices.size(); ++i) {
                            if (choices[i].name == "  Record Sequence" && choices[i].isOpen) {
                                int numOptions = 1;  // # options below current choice
                                choices.erase(choices.begin() + i + 1, choices.begin() + i + numOptions + 1);
                                choices[i].isOpen = false;  // Mark as closed
                                break;  // Stop after closing the Arps submenu
                            }
                        }
                        for (int i = 0; i < choices.size(); ++i) {
                            if (choices[i].name == "  Delete Take" && choices[i].isOpen) {
                                int numOptions = 2;  // # options below current choice
                                choices.erase(choices.begin() + i + 1, choices.begin() + i + numOptions + 1);
                                choices[i].isOpen = false;  // Mark as closed
                                break;  // Stop after closing the Arps submenu
                            }
                        }
                        for (int i = 0; i < choices.size(); ++i) {
                            if (choices[i].name == "  Select Song" && choices[i].isOpen) {
                                int numOptions = 2;  // # options below current choice
                                choices.erase(choices.begin() + i + 1, choices.begin() + i + numOptions + 1);
                                choices[i].isOpen = false;  // Mark as closed
                                break;  // Stop after closing the Arps submenu
                            }
                        }
                        for (int i = 0; i < choices.size(); ++i) {
                            if (choices[i].name == "  Delete Song" && choices[i].isOpen) {
                                int numOptions = 2;  // # options below current choice
                                choices.erase(choices.begin() + i + 1, choices.begin() + i + numOptions + 1);
                                choices[i].isOpen = false;  // Mark as closed
                                break;  // Stop after closing the Arps submenu
                            }
                        }
                        // Close Song Builder itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 5);  // # + 1
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
                        for (int i = 0; i < choices.size(); ++i) {
                            if (choices[i].name == "  Display Mappings" && choices[i].isOpen) {
                                int numOptions = 3;  // Number of options under choice
                                choices.erase(choices.begin() + i + 1, choices.begin() + i + numOptions + 1);
                                choices[i].isOpen = false;  // Mark as closed
                                break;  // Stop after closing the Arps submenu
                            }
                        }
                        for (int i = 0; i < choices.size(); ++i) {
                            if (choices[i].name == "  Remove Mapping" && choices[i].isOpen) {
                                int numOptions = 3;  // Number of options under choice
                                choices.erase(choices.begin() + i + 1, choices.begin() + i + numOptions + 1);
                                choices[i].isOpen = false;  // Mark as closed
                                break;  // Stop after closing the Arps submenu
                            }
                        }
                        // Close LFO Mappings itself
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 3);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        // ADD LEVEL TWO
                        int newIndent = choices[highlight].indentLevel;
                        addLevelTwo(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                
// L E V E L  T W O -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -
                
                // Synthesizer Mode
                if (choices[highlight].name == "  Choose Waveform") {
                    if (choices[highlight].isOpen) {
                        // CURRENTLY OPEN
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 9);  // # + 1
                        choices[highlight].isOpen = false;  // Mark as closed
                    } else {
                        // CURRENTLY CLOSED
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;   // Mark as open
                    }
                }
                
                // PRESETS
                if (choices[highlight].name == "  View Presets") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 3);  // # + 1
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                if (choices[highlight].name == "  Save as Preset") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 2);  // # + 1
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                
                // RECORD SAMPLE
                if (choices[highlight].name == "  Record Sample") {
                    // Record Audio. Also toggled by global button
                }
                // CHOOSE SAMPLE
                if (choices[highlight].name == "  Choose Sample") {
                    // CURRENTLY OPEN
                    if (choices[highlight].isOpen) {
                        // CLOSE LEVEL FIVE
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
                        
                        // CLOSE LEVEL FOUR
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
                if (choices[highlight].name == "  Record Sequence") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 2);  // # + 1
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                if (choices[highlight].name == "  Delete Take") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 3);  // # + 1
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                if (choices[highlight].name == "  Select Song") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 3);  // # + 1
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                if (choices[highlight].name == "  Delete Song") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 3);  // # + 1
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                
                // LFOs
                if (choices[highlight].name == "  Display Mappings") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 4);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                if (choices[highlight].name == "  Remove Mapping") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 4);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelThree(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                
// L E V E L  T H R E E --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
                
                // Choose Waveform
                if (choices[highlight].name == "    Saw") {
                    updateSample("    Saw");
                    playCurrentSample(currentSample);
                }
                if (choices[highlight].name == "    Sine") {
                    updateSample("    Sine");
                    playCurrentSample(currentSample);
                }
                if (choices[highlight].name == "    Square") {
                    updateSample("    Square");
                    playCurrentSample(currentSample);
                }
                if (choices[highlight].name == "    Triangle") {
                    updateSample("    Triangle");
                    playCurrentSample(currentSample);
                }
                if (choices[highlight].name == "    QuerppGrowl") {
                    updateSample("    QuerppGrowl");
                    playCurrentSample(currentSample);
                }
                if (choices[highlight].name == "    Glorkglunk") {
                    updateSample("    Glorkglunk");
                    playCurrentSample(currentSample);
                }
                if (choices[highlight].name == "    Dune") {
                    updateSample("    Dune");
                    playCurrentSample(currentSample);
                }
                if (choices[highlight].name == "    Grime") {
                    updateSample("    Grime");
                    playCurrentSample(currentSample);
                }
                
                // Choose Sample
                // SYNTHS------------------------------------------------------
                if (choices[highlight].name == "    Synths") {
                    // CURRENTLY OPEN
                    if (choices[highlight].isOpen) {
                        // CLOSE LEVEL FIVE
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
                        addLevelFour(highlight, newIndent);
                        choices[highlight].isOpen = true;
                    }
                }
                
                // INSTRUMENTS-------------------------------------------------
                if (choices[highlight].name == "    Instruments") {
                    // CURRENTLY OPEN
                    if (choices[highlight].isOpen) {
                        // CLOSE LEVEL 5
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
                        addLevelFour(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                
                // DRUMS-------------------------------------------------------
                if (choices[highlight].name == "    Drums") {
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
                        // CURRENTLY CLOSED
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);
                        choices[highlight].isOpen = true;
                    }
                }
                
                // MISC.
                if (choices[highlight].name == "    Misc.") {
                    if (choices[highlight].isOpen) {
                        choices.erase(choices.begin() + highlight + 1, choices.begin() + highlight + 20);  // +1 number of options
                        choices[highlight].isOpen = false;
                    } else {
                        int newIndent = choices[highlight].indentLevel;
                        addLevelFour(highlight, newIndent);
                        choices[highlight].isOpen = true;  // Mark as open
                    }
                }
                
                
                // L E V E L  F O U R ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- --
                vector<string> menuNames = {
                    "      Arps", "      Basses", "      Leads", "      Pads",
                    "      Brass", "      Choir", "      Strings", "      Harp", "      Guitar",
                    "      Kicks", "      Snares", "      Claps", "      Crashes",
                    "      HiHats", "      Rides", "      Toms", "      Other"
                };
                vector<int> menuOptions = {
                    7, 23, 8, 8,
                    5, 5, 5, 4, 5,
                    10, 12, 3, 3,
                    6, 5, 5, 7
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
                
// L E V E L  F I V E ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
                // P L A Y  A U D I O
                // Arps
                for (int i = 1; i <= 7; ++i) {
                    string arpName = "        Arp_" + to_string(i);
                    if (choices[highlight].name == arpName) {
                        updateSample(arpName);
                        playCurrentSample(currentSample);
                        break;  // Exit loop once the match is found
                    }
                }
                // Basses
                for (int i = 1; i <= 23; ++i) {
                    string bassName = "        Bass_" + to_string(i);
                    if (choices[highlight].name == bassName) {
                        updateSample(bassName);
                        playCurrentSample(currentSample);
                        break;  // Exit loop once the match is found
                    }
                }
                // Leads
                for (int i = 1; i <= 8; ++i) {
                    string leadName = "        Lead_" + to_string(i);
                    if (choices[highlight].name == leadName) {
                        updateSample(leadName);
                        playCurrentSample(currentSample);
                        break;  // Exit loop once the match is found
                    }
                }
                // Pads
                for (int i = 1; i <= 8; ++i) {
                    string padName = "        Pad_" + to_string(i);
                    if (choices[highlight].name == padName) {
                        updateSample(padName);
                        playCurrentSample(currentSample);
                        break;  // Exit loop once the match is found
                    }
                }
                // Brass
                for (int i = 1; i <= 5; ++i) {
                    string brassName = "        Brass_" + to_string(i);
                    if (choices[highlight].name == brassName) {
                        updateSample(brassName);
                        playCurrentSample(currentSample);
                        break;  // Exit loop once the match is found
                    }
                }
                // Choir
                for (int i = 1; i <= 5; ++i) {
                    string choirName = "        Choir_" + to_string(i);
                    if (choices[highlight].name == choirName) {
                        updateSample(choirName);
                        playCurrentSample(currentSample);
                        break;  // Exit loop once the match is found
                    }
                }
                // Strings
                for (int i = 1; i <= 5; ++i) {
                    string stringsName = "        Strings_" + to_string(i);
                    if (choices[highlight].name == stringsName) {
                        updateSample(stringsName);
                        playCurrentSample(currentSample);
                        break;  // Exit loop once the match is found
                    }
                }
                // Harps
                for (int i = 1; i <= 4; ++i) {
                    string harpName = "        Harp_" + to_string(i);
                    if (choices[highlight].name == harpName) {
                        updateSample(harpName);
                        playCurrentSample(currentSample);
                        break;  // Exit loop once the match is found
                    }
                }
                // Guitar
                for (int i = 1; i <= 5; ++i) {
                    string guitarName = "        Guitar_" + to_string(i);
                    if (choices[highlight].name == guitarName) {
                        updateSample(guitarName);
                        playCurrentSample(currentSample);
                        break;  // Exit loop once the match is found
                    }
                }
                // Kicks
                for (int i = 1; i <= 10; ++i) {
                    string kickName = "        Kick_" + to_string(i);
                    if (choices[highlight].name == kickName) {
                        updateSample(kickName);
                        playCurrentSample(currentSample);
                        break;  // Exit loop once the match is found
                    }
                }
                // Snares
                for (int i = 1; i <= 12; ++i) {
                    string snareName = "        Snare_" + to_string(i);
                    if (choices[highlight].name == snareName) {
                        updateSample(snareName);
                        playCurrentSample(currentSample);
                        break;  // Exit loop once the match is found
                    }
                }
                // Claps
                for (int i = 1; i <= 3; ++i) {
                    string clapName = "        Clap_" + to_string(i);
                    if (choices[highlight].name == clapName) {
                        updateSample(clapName);
                        playCurrentSample(currentSample);
                        break;  // Exit loop once the match is found
                    }
                }
                // Crashes
                for (int i = 1; i <= 3; ++i) {
                    string crashName = "        Crash_" + to_string(i);
                    if (choices[highlight].name == crashName) {
                        updateSample(crashName);
                        playCurrentSample(currentSample);
                        break;  // Exit loop once the match is found
                    }
                }
                // HiHats
                for (int i = 1; i <= 6; ++i) {
                    string hiHatName = "        HiHat_" + to_string(i);
                    if (choices[highlight].name == hiHatName) {
                        updateSample(hiHatName);
                        playCurrentSample(currentSample);
                        break;  // Exit loop once the match is found
                    }
                }
                // Rides
                for (int i = 1; i <= 5; ++i) {
                    string rideName = "        Ride_" + to_string(i);
                    if (choices[highlight].name == rideName) {
                        updateSample(rideName);
                        playCurrentSample(currentSample);
                        break;  // Exit loop once the match is found
                    }
                }
                // Toms
                for (int i = 1; i <= 5; ++i) {
                    string tomName = "        Tom_" + to_string(i);
                    if (choices[highlight].name == tomName) {
                        updateSample(tomName);
                        playCurrentSample(currentSample);
                        break;  // Exit loop once the match is found
                    }
                }
                // Other
                for (int i = 1; i <= 7; ++i) {
                    string otherName = "        Other_" + to_string(i);
                    if (choices[highlight].name == otherName) {
                        updateSample(otherName);
                        playCurrentSample(currentSample);
                        break;  // Exit loop once the match is found
                    }
                }
                // Misc.
                for (int i = 1; i <= 19; ++i) {
                    string miscName = "      Misc_" + to_string(i);
                    if (choices[highlight].name == miscName) {
                        updateSample(miscName);
                        playCurrentSample(currentSample);
                        break;  // Exit loop once the match is found
                    }
                }
                
                // E X I T from L E V E L  O N E
                if (choices[highlight].name == "Exit")
                {
                    endwin();
                    exit(0);
                }
                break;
            }
        }
    }
    return 0;
}

#ifndef MENUFUNCTIONS_H
#define MENUFUNCTIONS_H

#include "GlobalVariables.h"

struct MenuItem
{
    bool hasMiniSubs;           // Flag to track if the submenu already has minisubs
    bool isMiniSub;             // Flag to indicate if this is a minisub option
    bool isOpen;                // To track if the submenu is open (has sub-items)
    int indentLevel;
    string name;
    
    // Constructor for MenuItem
    MenuItem(const string& n, int i, bool minisub = false, bool has_subs = false, bool open = false);
};

// Function declarations
void clearScreen();
void ncursesInitialize();
void openingAnimation();
void playAudioByName(int highlight, const string& name);
void playAudioFromCategory(int highlight, const string& category, int count);
void addLevelOne();
void addLevelTwo(int startIndex, int subIndent);
void addLevelThree(int startIndex, int subIndent);
void addLevelFour(int startIndex, int subIndent);
void addLevelFive(int startIndex, int subIndent);
void setCurrSample(string newSample);
extern vector<MenuItem> choices;

#endif // MENUFUNCTIONS_H

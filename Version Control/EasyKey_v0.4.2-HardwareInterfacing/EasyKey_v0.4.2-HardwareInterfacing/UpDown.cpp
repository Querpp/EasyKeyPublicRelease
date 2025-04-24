#include "UpDown.h"

// Allows user to edit lowpass filter frequency
void ChangeLowpassFrequency(int& ValueToEdit, WINDOW* menuWindow)
{
    keypad(menuWindow, TRUE);  // Enable arrow key input
    
    while (true) {
        
        // Read key input from the window
        int ch = wgetch(menuWindow);
        
        switch (ch) {
            case KEY_UP:
                ValueToEdit += 100;
                break;
            case KEY_DOWN:
                ValueToEdit -= 100;
                break;
            case 'q':  // Quit on 'q'
                return;
        }
    }
}

// Allows user to change lowpass filter slope
void ChangeLowpassSlope(int& ValueToEdit, WINDOW* menuWindow)
{
    // Cuttoff, Order
    // 1, 6
    // 2, 12
    // 3, 18
    // 4, 24
    // 5, 30
    // 6, 36
    // 7, 42
    // 8, 48
    // 9, 54
    // 10, 60
    // 12, 72
    // 14, 84
    // 16, 96
    
    keypad(menuWindow, TRUE);  // Enable arrow key input
    
    while (true) {
        // Refresh edge cases
        if (ValueToEdit < 1) ValueToEdit = 10;
        if (ValueToEdit > 16) ValueToEdit = 10;
        
        // Read key input from the window
        int ch = wgetch(menuWindow);
        
        switch (ch) {
            case KEY_UP:
                ValueToEdit += 2;
                break;
            case KEY_DOWN:
                ValueToEdit -= 2;
                break;
            case 'q':  // Quit on 'q'
                return;
        }
    }
}


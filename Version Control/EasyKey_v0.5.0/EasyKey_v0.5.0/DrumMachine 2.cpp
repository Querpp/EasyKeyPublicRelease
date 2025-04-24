#include "DrumMachine.h"

// Rotates chosen sample for drum machine
void sampleRotater(string sampleName)
{
    // 1. Rotate Array
    DrumMachine[4] = DrumMachine[3];    // 5th is old 4th
    DrumMachine[3] = DrumMachine[2];    // 4th is old 3rd
    DrumMachine[2] = DrumMachine[1];    // 3rd is old 2nd
    DrumMachine[1] = DrumMachine[0];    // 2nd is old 1st
    
    // 2. Set sampleName to array head
    DrumMachine[0] = sampleName;
}

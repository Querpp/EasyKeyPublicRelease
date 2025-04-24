#include "UserCreate.h"


string generateRandomString()
{
    const string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<unsigned long> distribution(0, charset.size() - 1);
    
    string randomString;
    for (int i = 0; i < 5; i++) {
        randomString += charset[distribution(generator)];
    }
    return randomString;
}


void createPreset()
{
    // Incase a heathen deletes from initialized vector
    if (usrPresets.empty()) usrPresets.push_back("    Really?");
    
    // Remove "No Presets" if it's the first element
    if (usrPresets.front() == "    No Presets")
    {
        usrPresets.erase(usrPresets.begin());           // Erase "No Presets"
        string tempPreset = generateRandomString();     // Generate Preset Name
        usrPresets.push_back("    " + tempPreset);
    } else {
        // Generate Preset Name
        string tempPreset = generateRandomString();
        usrPresets.push_back("    " + tempPreset);
    }
}


void createSong()
{
    // Incase a heathen deletes from initialized vector
    if (usrSongs.empty()) usrSongs.push_back("    Really?");
    
    // Remove "No Songs" if it's the first element
    if (usrSongs.front() == "    No Songs")
    {
        usrSongs.erase(usrSongs.begin());               // Erase "No Songs"
        string tempPreset = generateRandomString();     // Generate Preset Name
        usrSongs.push_back("    " + tempPreset);
    } else {
        // Generate Song Name
        string tempPreset = generateRandomString();
        usrSongs.push_back("    " + tempPreset);
    }
}

void createSequence()
{
    // Incase a heathen deletes from initialized vector
    if (usrTakes.empty()) usrTakes.push_back("    Really?");
    
    // Remove "No Songs" if it's the first element
    if (usrTakes.front() == "    No Sequences")
    {
        usrTakes.erase(usrTakes.begin());               // Erase "No Sequences"
        string tempPreset = generateRandomString();     // Generate Preset Name
        usrTakes.push_back("    " + tempPreset);
    } else {
        // Generate Song Name
        string tempPreset = generateRandomString();
        usrTakes.push_back("    " + tempPreset);
    }
}

void createLFO()
{
    // Incase a heathen deletes from initialized vector
    if (LFOmappings.empty()) LFOmappings.push_back("    Really?");
    
    // Remove "No LFOs" if it's the first element
    if (LFOmappings.front() == "    No LFOs")
    {
        LFOmappings.erase(LFOmappings.begin());
        LFOmappings.push_back("    LFO_1 -> DistortionDrive");
    } else {
        // Add mappings based on the size of LFOmappings
        if (LFOmappings.size() == 1) {
            LFOmappings.push_back("    LFO_2 -> DistortionDrive");
        }
        else if (LFOmappings.size() == 2) {
            LFOmappings.push_back("    LFO_3 -> DistortionDrive");
        }
        else if (LFOmappings.size() == 3) {
            LFOmappings.push_back("    LFO_4 -> DistortionDrive");
        }
        else if (LFOmappings.size() == 4) {
            LFOmappings.push_back("    LFO_5 -> DistortionDrive");
        }
        else {
            // Handle cases where LFOmappings has more than 5 elements
            LFOmappings.push_back("    Additional LFO mapping...");
        }
    }
}

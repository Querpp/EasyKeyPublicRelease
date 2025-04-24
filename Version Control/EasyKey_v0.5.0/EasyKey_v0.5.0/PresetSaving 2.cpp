#include "PresetSaving.h"
#include "UserCreate.h"
#include "Paths.h"

#include <cstdio>
#include <ctime>
#include <dirent.h>
#include <fstream>
#include <unistd.h>

// Structure for dummy LFOs in this file
struct LFOmappingType
{
    string LFOname;
    string hostLFO;
    string Waveform;
    string LFOspeed;
    string LFOsend;
};



// Convert WaveType to string
string to_string(WaveType type) {
    switch (type) {
        case WaveType::SAW:         return "SAW";
        case WaveType::SQUARE:      return "SQUARE";
        case WaveType::SINE:        return "SINE";
        case WaveType::GLORKGLUNK:  return "GLORKGLUNK";
        case WaveType::DRUMFILL:    return "DRUMFILL";
        case WaveType::DUNE:        return "DUNE";
        case WaveType::PROCESSED:   return "PROCESSED";
        default:                    return "UNKNOWN";
    }
}

// Refresh the global usrPresets vector with all found preset names
void refreshUsrPresets()
{
    usrPresets.clear();
    
    string path = getPresetPath();
    vector<string> foundPresets = getTxtFiles(path);
    
    if (foundPresets.empty()) {
        usrPresets.push_back("    No Presets");
        return;
    }
    
    for (const auto& file : foundPresets) {
        string displayName = file.substr(0, file.size() - 4); // remove ".txt"
        usrPresets.push_back("    " + displayName);
    }
}

// Save the current settings as a preset
void createPreset()
{
    if (usrPresets.empty()) usrPresets.push_back("    Really?");
    
    if (usrPresets.front() == "    No Presets") {
        usrPresets.erase(usrPresets.begin());
    }
    
    string tempPreset = generateRandomString();
    usrPresets.push_back("    " + tempPreset);
    
    vector<LFOmappingType> LFOlist;
    
    // Dummy LFOs
    LFOlist.push_back({
        generateRandomString(),
        "LFO1",
        "Sine",
        "1.25Hz",
        "Filter Cutoff"
    });
    // Dummy LFOs
    LFOlist.push_back({
        generateRandomString(),
        "LFO2",
        "Square",
        "0.5Hz",
        "Reverb Mix"
    });
    
    time_t timestamp;
    time(&timestamp);
    
    string basePath = getPresetPath();
    string filePath = basePath + "/" + tempPreset + ".txt";
    
    // Create File
    ofstream outfile(filePath);
    
    // Populate File
    outfile << "Preset: " << tempPreset << endl;
    outfile << ctime(&timestamp) << endl;
    
    // Oscillators
    outfile << "Oscillator Engine " << endl;
    outfile << "   Wavetype: " << to_string(currentWaveType) << endl << endl;
    
    // Effects
    outfile << "Effects Settings: " << endl;
    outfile << "   Distortion Settings " << endl;
    outfile << "      Distortion Algorithm: " << KNOB_DistAlg << endl;
    outfile << "      Distortion Drive: " << KNOB_DistDrive << endl;
    outfile << "   Flanger Settings " << endl;
    outfile << "      Flanger Rate: " << KNOB_FlgRate << endl;
    outfile << "      Flanger Mix: " << KNOB_FlgMix << endl;
    outfile << "   Phaser Settings " << endl;
    outfile << "      Phaser Rate: " << KNOB_FlgRate << endl;
    outfile << "      Phaser Mix: " << KNOB_FlgMix << endl;
    outfile << "   Lowpass Filter Settings " << endl;
    outfile << "      Frequency Position: " << KNOB_FltLP << endl;
    outfile << "      Filter Q Value: " << KNOB_FltQ << endl;
    outfile << "   Echo Settings " << endl;
    outfile << "      Echo Frequency: " << KNOB_EchFreq << endl;
    outfile << "      Echo Mix: " << KNOB_EchMix << endl;
    outfile << "   Reverb Settings " << endl;
    outfile << "      Reverb Decay: " << KNOB_VerbDcy << endl;
    outfile << "      Reverb Mix: " << KNOB_VerbMix << endl << endl;
    
    // LFOs
    outfile << "LFO Settings: " << endl;
    for (const auto& currLFO : LFOlist)
    {
        outfile << "   LFO Name: " << currLFO.LFOname << endl;
        outfile << "      Host LFO: " << currLFO.hostLFO << endl;
        outfile << "      Waveform: " << currLFO.Waveform << endl;
        outfile << "      Speed: " << currLFO.LFOspeed << endl;
        outfile << "      Send Target: " << currLFO.LFOsend << endl;
    }
    outfile << endl;
    
    // Envelope
    outfile << "Envelope: " << endl;
    outfile << "   Attack: " << "KNOB_EnvAttack" << endl;
    outfile << "   Decay: " << "KNOB_EnvDcy" << endl;
    outfile << "   Sustain: " << "KNOB_EnvSus" << endl;
    outfile << "   Release: " << "KNOB_EnvRel" << endl;
    
    // End file writing
    outfile.close();
    cout << "File saved to: " << filePath << endl;
}


// Helper: Strip "    " and add .txt to match file names
vector<string> getExpectedFilenames() {
    vector<string> expected;
    for (const auto& name : usrPresets) {
        if (name != "    No Presets" && name.length() > 4)
            expected.push_back(name.substr(4) + ".txt");
    }
    return expected;
}


// Delete .txt files
void cleanUpPresets() {
    string path = getPresetPath();
    vector<string> expectedFiles = getExpectedFilenames();
    
    DIR* dir = opendir(path.c_str());
    if (!dir) {
        cerr << "Error: Could not open preset directory." << endl;
        return;
    }
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        string fileName = entry->d_name;
        
        // Skip non-txt files
        if (fileName.length() < 4 || fileName.substr(fileName.length() - 4) != ".txt")
            continue;
        
        // If file not in expected list, delete it
        if (find(expectedFiles.begin(), expectedFiles.end(), fileName) == expectedFiles.end())
        {
            string fullPath = path + "/" + fileName;
            if (remove(fullPath.c_str()) == 0) {
                cout << "Deleted orphaned preset: " << fileName << endl;
            } else {
                cerr << "Failed to delete: " << fileName << endl;
            }
        }
    }
    closedir(dir);
}

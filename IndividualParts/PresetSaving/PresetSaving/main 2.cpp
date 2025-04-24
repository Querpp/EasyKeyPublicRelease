#include <ctime>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <random>
#include <string>
#include <unistd.h>
using namespace std;

// Generate random 5 character string
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

// Get directory for saving presets
string getBasePath()
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        cerr << "Error getting current directory" << endl;
        return "";
    }
    return string(cwd) + "/PresetSaving/PresetSaving";
}

// LFO data structure
struct LFOmapping
{
    string LFOname;
    string hostLFO;
    string Waveform;
    string LFOspeed;
    string LFOsend;
};

//---------------------------------------------------------------------------------------------------------------------

int main()
{
    // Effects Knobs
    int KNOB_DistAlg = 1;
    int KNOB_DistDrive = 2;
    int KNOB_FlgRate = 3;
    int KNOB_FlgMix = 4;
    int KNOB_PhsRate = 5;
    int KNOB_PhsMix = 6;
    int KNOB_FltLP = 7;
    int KNOB_FltQ = 8;
    int KNOB_EchFreq = 9;
    int KNOB_EchMix = 10;
    int KNOB_VerbDcy = 11;
    int KNOB_VerbMix = 12;
    
    // Envelope
    int KNOB_EnvAttack = 13;
    int KNOB_EnvDcy = 14;
    int KNOB_EnvSus = 15;
    int KNOB_EnvRel = 16;
    
    vector<string> usrPresets;
    vector<LFOmapping> LFOlist;
    string waveType = "SAW";
    
    // Add a few dummy LFO mappings
    LFOmapping lfo;
    lfo.LFOname = generateRandomString();
    lfo.hostLFO = "LFO1";
    lfo.Waveform = "Sine";
    lfo.LFOspeed = "1.25Hz";
    lfo.LFOsend = "Filter Cutoff";
    
    LFOlist.push_back(lfo);
    
    LFOlist.push_back({
        generateRandomString(),
        "LFO2",
        "Square",
        "0.5Hz",
        "Reverb Mix"
    });
    
    string presetName = generateRandomString();
    time_t timestamp;
    time(&timestamp);
    
    string basePath = getBasePath();
    string filePath = basePath + "/" + presetName + ".txt";
    
    ofstream outfile(filePath);
    if (!outfile.is_open()) {
        cerr << "Failed to open file at: " << filePath << endl;
        return 1;
    }
    
    
    // Print to preset txt file
    outfile << "Preset: " + presetName << endl;     // Preset Name
    outfile << ctime(&timestamp) << endl;           // Date + Time
    
    // Oscillator Engine
    outfile << "Oscillator Engine " << endl;
    outfile << "   Wavetype: " << waveType << endl << endl;
    
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
    outfile << "   Attack: " << KNOB_EnvAttack << endl;
    outfile << "   Decay: " << KNOB_EnvDcy << endl;
    outfile << "   Sustain: " << KNOB_EnvSus << endl;
    outfile << "   Release: " << KNOB_EnvRel << endl;
    
    // Close file writing stream
    outfile.close();
    cout << "File saved to: " << filePath << endl;
    
    return 0;
}

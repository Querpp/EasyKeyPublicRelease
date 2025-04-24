#include "audioPlayer.h"


// Function to play audio using afplay
void playAudio(const string& filePath) {
    string command = "aplay " + filePath + " > /dev/null 2>&1";  // Command to play audio
    system(command.c_str());  // Execute the command to play the audio
}

// Function to launch audio playback in a separate thread
void playAudioThreaded(const string& filePath) {
    thread audioThread(playAudio, filePath);
    audioThread.detach();  // Detach the thread to let it run independently
}

// Function that plays audio based on file path and adjusts pitch
void playCurrentSample(string guyChosen, float pitchFactor)
{
    ofstream myFile("audioPlayerDEBUG.txt"); // Creates and opens "example.txt" in the current working directory
    
    // Remove leading spaces
    guyChosen.erase(guyChosen.begin(), find_if(guyChosen.begin(), guyChosen.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
    
    string BASE_PATH = "/home/easykey/Menu_v3/SampleLibrary/";   // Relative path
    
    myFile << "BASE_PATH: " << BASE_PATH << endl;
    string FILE_PATH = BASE_PATH + guyChosen + ".wav";
    myFile << "FILE_PATH: " << FILE_PATH << endl;
    
    playAudioThreaded(FILE_PATH);  // Call the threaded version
}

#include "AudioPlayer.h"
#include <fstream>

// Function to play audio using afplay
void playAudio(const string& filePath)
{
    string command = "afplay " + filePath;
    system(command.c_str());
}

// Function to launch audio playback in a separate thread
void playAudioThreaded(const string& filePath)
{
    thread audioThread(playAudio, filePath);
    audioThread.detach();  // Detach the thread to let it run independently
}

// Function to construct the full file path, remove leading spaces, and play audio
void filePath(string smplChosen)
{
    ofstream myFile("/Users/ethanlaptew/Desktop/example.txt"); // Creates and opens "example.txt"
    
    // Remove leading spaces
    smplChosen.erase(smplChosen.begin(), find_if(smplChosen.begin(), smplChosen.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
    string BASE_PATH = "/Users/ethanlaptew/Documents/GitHub/EasyKey/ScrollableMenu/ScrollableMenu/Resources/SampleLibrary/";
    
    myFile << "BASE_PATH: " << BASE_PATH << endl;
    string FILE_PATH = BASE_PATH + smplChosen + ".wav";
    myFile << "FILE_PATH: " << FILE_PATH << endl;
    
    playAudioThreaded(FILE_PATH);  // Call the threaded version
}

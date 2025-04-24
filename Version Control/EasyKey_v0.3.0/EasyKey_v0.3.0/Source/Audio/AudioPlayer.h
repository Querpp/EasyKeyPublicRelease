#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "GlobalVariables.h"

void playAudio(const string& filePath);                 // Function to play audio using afplay
void playAudioThreaded(const string& filePath);         // Function to launch audio playback in a separate thread
void playCurrentSample(std::string guyChosen, float pitchFactor = 1.0f);

#endif // AUDIOPLAYER_H

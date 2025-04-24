#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include <vector>
using namespace std;

void playAudio(const string& filePath);             // Function to play audio using afplay
void playAudioThreaded(const string& filePath);     // Function to launch audio playback in a separate thread
void filePath(string smplChosen);                   // Function to construct the full file path, remove leading spaces, and play audio

#endif // AUDIOPLAYER_H

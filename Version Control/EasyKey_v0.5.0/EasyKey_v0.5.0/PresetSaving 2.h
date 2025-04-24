#ifndef PRESETSAVING_H
#define PRESETSAVING_H

#include "GlobalVariables.h"

vector<string> getTxtFiles(const string& directoryPath);
string getPresetPath();
string to_string(WaveType type);
void refreshUsrPresets();
void createPreset();
void cleanUpPresets();

#endif // PRESETSAVING_H

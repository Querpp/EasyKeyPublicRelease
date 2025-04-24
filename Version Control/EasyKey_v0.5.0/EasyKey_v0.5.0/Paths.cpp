#include "Paths.h"

// SampleLibrary
string getBasePath()
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        cerr << "Error getting current directory" << endl;
        return "";
    }
    return string(cwd) + "/Resources/SampleLibrary/";
//    return "/home/easykey/EasyKey_v0.5.0/EasyKey_v0.5.0";
}

// Wavetables
string getWavePath()
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        cerr << "Error getting current directory" << endl;
        return "";
    }
    return string(cwd) + "/Resources/Wavetables/";
//    return "/home/easykey/EasyKey_v0.5.0/EasyKey_v0.5.0";
}


// Presets
string getPresetPath()
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        cerr << "Error getting current directory" << endl;
        return "";
    }
    return string(cwd) + "/Resources/UserPresets";
//    return "/home/easykey/EasyKey_v0.5.0/EasyKey_v0.5.0";
}

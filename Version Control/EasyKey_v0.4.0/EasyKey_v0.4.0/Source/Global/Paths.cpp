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
}

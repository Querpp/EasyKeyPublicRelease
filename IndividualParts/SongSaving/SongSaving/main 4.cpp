#include <iostream>
#include <string>
#include <filesystem>
#include <random>
#include <unistd.h>   // for getcwd
#include <limits.h>   // for PATH_MAX

using namespace std;
namespace fs = std::filesystem;

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

// Get current working directory path
string getSongPath()
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        cerr << "Error getting current directory" << endl;
        return "";
    }
    
    return string(cwd) + "/SongSaving/SongSaving";
}

void createSong()
{
    string parentDir = getSongPath(); // Use your function here
    string folderName = generateRandomString();
    
    fs::path fullPath = fs::path(parentDir) / folderName;
    
    try {
        if (fs::create_directories(fullPath)) { // makes intermediate dirs too
            cout << "Folder created at: " << fullPath << endl;
        } else {
            cout << "Folder already exists or could not be created." << endl;
        }
    } catch (fs::filesystem_error& error) {
        cerr << "Filesystem error: " << error.what() << endl;
    }
}

int main()
{
    cout << "Current working directory: " << getSongPath() << endl;
    createSong();
    return 0;
}

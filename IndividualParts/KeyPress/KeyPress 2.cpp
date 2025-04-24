#include <iostream>
#include <fstream>
#include <termios.h>
#include <unistd.h>

using namespace std;

char getKeyPress() {
    struct termios oldt, newt;
    char ch;
    
    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    
    // Disable canonical mode and echo
    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_cc[VMIN] = 1; // Minimum number of characters to read (1)
    newt.c_cc[VTIME] = 0; // Timeout for input (no timeout)
    
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    // Read a single character
    ch = getchar();
    
    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    return ch;
}

int main() {
    // Open output file in the same directory as the executable
    ofstream outFile("MY_OUTPUT_NOW.txt");
    
    if (!outFile.is_open()) {
        cerr << "Error opening file for writing!" << endl;
        return 1;
    }
    
    cout << "Press any key (Press 'q' to quit): " << endl;
    outFile << "Press any key (Press 'q' to quit): " << endl;
    
    char key;
    while (true) {
        key = getKeyPress();
        cout << "You pressed: " << key << endl;
        outFile << "You pressed: " << key << endl;
        
        if (key == 'q') {
            cout << "Exiting..." << endl;
            outFile << "Exiting..." << endl;
            break;
        }
    }
    
    outFile.close(); // Close the file
    return 0;
}
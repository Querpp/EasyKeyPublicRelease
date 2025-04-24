#include "KeyPress.h"

void keyPress()
{
    // Get current time as system time
    auto now = chrono::system_clock::now();
    
    // Convert to time_t to use in localtime
    time_t now_time_t = chrono::system_clock::to_time_t(now);
    
    // Open output file in the same directory as the executable
    ofstream outFile("/Users/ethanlaptew/Documents/GitHub/EasyKey/ScrollableMenu/ScrollableMenu/Resources/recordSequence.txt");
    
    // Print current date and time to the file
    outFile << put_time(localtime(&now_time_t), "%Y-%m-%d %H:%M:%S") << endl;
    
    outFile << "Press any key (Press 'q' to quit): " << endl;
    
    struct termios oldt, newt;
    char key;
    
    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    
    // Disable canonical mode and echo
    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_cc[VMIN] = 1; // Minimum number of characters to read (1)
    newt.c_cc[VTIME] = 0; // Timeout for input (no timeout)
    
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    while (true) {
        // Read a single character (non-blocking)
        if (read(STDIN_FILENO, &key, 1) == 1) {
            // If a character is read, output it
            outFile << "You pressed: " << key << endl;
            outFile.flush(); // Ensure immediate writing to the file
            
            // Check for exit condition (q, Q, or ESC)
            if (key == 'q' || key == 'Q' || key == 27) {
                outFile << "Exiting..." << endl;
                break;
            }
        }
        usleep(10); // Sleep for a short duration to prevent high CPU usage
    }
    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    outFile.close(); // Close the file
}

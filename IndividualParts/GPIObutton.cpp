// Courtney Jones
// Test if the button would be detected.
// It would show ‘button is released’ if no press and ‘button is pressed’ when pressed.

#include <iostream>
#include <pigpio.h>
using namespace std;

const int BUTTON_GPIO = 2;

int main()
{
    if (gpioInitialise() < 0) {
        cerr << "Failed to initialize" << endl;
        return 1;
    }
    
    gpioSetMode(BUTTON_GPIO, PI_INPUT);
    gpioSetPullUpDown(BUTTON_GPIO, PI_PUD_UP); //PULL-UP resister
    
    cout << "Monitoring button on GPIO " << BUTTON_GPIO << " (Press Ctrl+C to exit)\n";
    
    while (true)
    {
        int state = gpioRead(BUTTON_GPIO);
        if (state == 0) {
            cout << "Button pressed!\n";
        }
        else {
            cout << "Button is Released.\n";
        }
        gpioDelay(300000);
    }
    
    gpioTerminate();
    return 0;
}

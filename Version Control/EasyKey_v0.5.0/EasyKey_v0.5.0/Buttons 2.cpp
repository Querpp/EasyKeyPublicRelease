#include "Buttons.h"

void initButtons()
{ 
    // Define buttons
    gpioSetMode(BUTTON_UPARROW, PI_INPUT);
    gpioSetPullUpDown(BUTTON_UPARROW, PI_PUD_UP);
    gpioSetMode(BUTTON_DOWNARROW, PI_INPUT);
    gpioSetPullUpDown(BUTTON_DOWNARROW, PI_PUD_UP);
    gpioSetMode(BUTTON_ENTER, PI_INPUT);
    gpioSetPullUpDown(BUTTON_ENTER, PI_PUD_UP);
    gpioSetMode(BUTTON_APPLYCHANGES, PI_INPUT);
    gpioSetPullUpDown(BUTTON_APPLYCHANGES, PI_PUD_UP);
}

// Courtney Jones
//  Test to see if the values of the potentiometers were read by turning the knobs

#include <iostream>
#include <pigpio.h>
using namespace std;

#define SPI_CHANNEL 1
#define SPI_SPEED 1350000 // 1.35 MHz SPI speed

// Function to read analog value from MCP3008 ADC via SPI
int readADC(int channel)
{
    // tx[]: transmit buffer to send SPI command
    // - 1: start bit
    // - (8 + channel) << 4: single-ended mode + channel number
    // - 0: don't care, needed to complete 3-byte transfer
    char tx[3] = {1, (char)((8 + channel) << 4), 0};
    
    // rx[]: receive buffer to store the response from ADC
    char rx[3] = {0, 0, 0};
    
    // Open SPI connection on channel 1, speed 1 MHz, mode 0
    int handle = spiOpen(1, 1000000, 0);    // Channel 1 is an ADC
    if (handle < 0) {
        cerr << "Failed to open SPI" << endl;
        return -1;
    }
    
    // Perform SPI transaction: send tx[], receive into rx[]
    spiXfer(handle, tx, rx, 3);
    
    // Close SPI connection
    spiClose(handle);
    
    // Extract 10-bit value from response:
    // - rx[1] & 3 gives the two MSBs
    // - rx[2] gives the lower 8 bits
    int value = ((rx[1] & 3) << 8) | rx[2];
    return value;
}

int main()
{
    // Initialize the pigpio library
    if (gpioInitialise() < 0) {
        cerr << "Failed to initialize pigpio" << endl;
        return 1;
    }
    
    // Infinite loop to continuously read and print values
    while (true)
    {
        // Read analog values from channels 0 and 1
        int value0 = readADC(0);
        int value1 = readADC(1);
        
        // Print the values to the console
        cout << "Pot1: " << value0 << " | Pot2: " << value1 << endl;
        
        // Delay for 500 milliseconds (500,000 microseconds)
        gpioDelay(500000);
    }
    
    // Cleanly shut down pigpio (this is unreachable in current loop)
    gpioTerminate();
    return 0;
}

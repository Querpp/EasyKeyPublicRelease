// Courtney Jones
// Check if it was possible to increase the volume of the speaker.

#include <alsa/asoundlib.h>
#include <cmath>
#include <iostream>
#include <pigpio.h>

#define PCM_DEVICE "sysdefault:CARD=sndrpihifiberry"


// Read MCP3008 channel via software chip select
int readPot(int csPin, int channel) {
    char tx[3] = {1, (char)((8 + channel) << 4), 0};
    char rx[3] = {0};
    
    int handle = spiOpen(0, 1000000, 0);  // SPI0, 1MHz, mode 0
    if (handle < 0) {
        std::cerr << "SPI open failed" << std::endl;
        return -1;
    }
    
    gpioWrite(csPin, 0);
    spiXfer(handle, tx, rx, 3);
    gpioWrite(csPin, 1);
    
    spiClose(handle);
    
    return ((rx[1] & 3) << 8) | rx[2];  // 10-bit result: 0–1023
}

int main() {
    // ALSA setup
    snd_pcm_t *pcmHandle;
    snd_pcm_hw_params_t *params;
    
    int rate = 44100;
    int channels = 1;
    snd_pcm_uframes_t frames;
    int16_t *buffer;
    
    if (snd_pcm_open(&pcmHandle, PCM_DEVICE, SND_PCM_STREAM_PLAYBACK, 0) < 0) {
        std::cerr << "Failed to open PCM device." << std::endl;
        return 1;
    }
    
    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(pcmHandle, params);
    snd_pcm_hw_params_set_access(pcmHandle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(pcmHandle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(pcmHandle, params, channels);
    snd_pcm_hw_params_set_rate_near(pcmHandle, params, (unsigned int *)&rate, nullptr);
    snd_pcm_hw_params_set_period_size_near(pcmHandle, params, &frames, nullptr);
    snd_pcm_hw_params(pcmHandle, params);
    snd_pcm_hw_params_get_period_size(params, &frames, nullptr);
    buffer = new int16_t[frames];
    
    // pigpio setup
    if (gpioInitialise() < 0) {
        std::cerr << "pigpio init failed." << std::endl;
        return 1;
    }
    
    const int csPin = 26;
    gpioSetMode(csPin, PI_OUTPUT);
    gpioWrite(csPin, 1);
    
    double freq = 440.0;
    double phase = 0.0;
    double phaseInc = 2 * M_PI * freq / rate;
    
    while (true) {
        int potVal = readPot(csPin, 5);  // Volume pot: 0–1023
        double volume = potVal / 1023.0;
        
        for (unsigned int i = 0; i < frames; ++i) {
            double sample = sin(phase) * volume * 30000;
            buffer[i] = (int16_t)sample;
            phase += phaseInc;
            if (phase > 2 * M_PI) phase -= 2 * M_PI;
        }
        
        int err = snd_pcm_writei(pcmHandle, buffer, frames);
        if (err == -EPIPE) {
            snd_pcm_prepare(pcmHandle);
        }
    }
    
    delete[] buffer;
    snd_pcm_drain(pcmHandle);
    snd_pcm_close(pcmHandle);
    gpioTerminate();
    return 0;
}

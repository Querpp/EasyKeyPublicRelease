// Courtney Jones
// Test if the speaker could make a sound directly from a code.

#include <iostream>
#include <cmath>
#include <alsa/asoundlib.h>

#define SAMPLE_RATE 44100
#define AMPLITUDE 0.5
#define FREQUENCY 440  // Frequency in Hz (A4 note)

int main() {
    snd_pcm_t *handle;
    snd_pcm_hw_params_t *params;
    snd_pcm_uframes_t frames;
    int err;
    unsigned int rate = SAMPLE_RATE;

    // Open PCM device for playback.
    err = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
    if (err < 0) {
        std::cerr << "Error opening PCM device: " << snd_strerror(err) << std::endl;
        return -1;
    }

    // Set hardware parameters.
    snd_pcm_hw_params_alloca(&params);
    err = snd_pcm_hw_params_any(handle, params);
    if (err < 0) {
        std::cerr << "Error setting default parameters: " << snd_strerror(err) << std::endl;
        return -1;
    }

    err = snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    err = snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
    err = snd_pcm_hw_params_set_channels(handle, params, 1);  // Mono sound
    err = snd_pcm_hw_params_set_rate_near(handle, params, &rate, 0);
    err = snd_pcm_hw_params(handle, params);
    if (err < 0) {
        std::cerr << "Error setting PCM parameters: " << snd_strerror(err) << std::endl;
        return -1;
    }

    frames = 32;  // Number of frames per period

    // Generate sine wave samples.
    short buffer[frames];
    for (int i = 0; i < frames; ++i) {
        float sample = AMPLITUDE * std::sin(2 * M_PI * FREQUENCY * i / SAMPLE_RATE);
        buffer[i] = static_cast<short>(sample * 32767);  // Convert to 16-bit signed PCM format
    }

    // Play sound in an infinite loop.
    while (true) {
        err = snd_pcm_writei(handle, buffer, frames);
        if (err == -EPIPE) {
            // Overrun occurred, recover by dropping some data.
            std::cerr << "Overrun occurred" << std::endl;
            snd_pcm_prepare(handle);
        } else if (err < 0) {
            std::cerr << "Error writing to PCM device: " << snd_strerror(err) << std::endl;
            break;
        }
    }

    snd_pcm_close(handle);
    return 0;
}

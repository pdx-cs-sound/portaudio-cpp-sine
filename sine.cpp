// Play a one-second 1KHz sine wave.
// Bart Massey 2024-03

#include <portaudio.h>
#include <iostream>
#include <unistd.h>
#include <math.h>

using namespace std;

int main() {
    PaError e1 = Pa_Initialize();
    if (e1 != paNoError) {
        cerr << "Pa_Initialize: " << Pa_GetErrorText(e1);
        exit(1);
    }
    PaDeviceIndex device = Pa_GetDefaultOutputDevice();
    PaStream *pa;
    PaStreamParameters params = {
        .device = device,
        .channelCount = 1,
        .sampleFormat = paFloat32,
        .suggestedLatency = 0,
        .hostApiSpecificStreamInfo = 0,
    };
    PaError e2 = Pa_OpenStream(&pa, 0, &params, 48000, 48, paNoFlag, 0, 0);
    if (e2 != paNoError) {
        cerr << "Pa_OpenStream: " << Pa_GetErrorText(e2);
        exit(1);
    }
    Pa_StartStream(pa);

    float frames[48];
    for (int t = 0; t < 48; t++) {
        frames[t] = 0.8 * sinf((float) t * 2.0 * M_PI / 48.0);
    }
    for (int i = 0; i < 1000; i++) {
        Pa_WriteStream(pa, frames, 48);
    }

    Pa_Terminate();
}

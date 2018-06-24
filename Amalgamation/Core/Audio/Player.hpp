#pragma once

#include <portaudio.h>

#define PORTAUDIO_CALLBACK(x) int x ( const void *InputBuffer, void *OutputBuffer, \
                           unsigned long FramesPerBuffer, \
                           const PaStreamCallbackTimeInfo* TimeInfo, \
                           PaStreamCallbackFlags StatusFlags, \
                           void *UserData )

#define PORTAUDIO_CALLBACK_LAMDA(capture) [capture]( const void *InputBuffer, void *OutputBuffer, \
                           unsigned long FramesPerBuffer, \
                           const PaStreamCallbackTimeInfo* TimeInfo, \
                           PaStreamCallbackFlags StatusFlags, \
                           void *UserData ) -> int

namespace Amalgamation {



}
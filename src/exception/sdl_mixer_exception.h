#ifndef CHOMP_EXCEPTION_SDL_MIX
#define CHOMP_EXCEPTION_SDL_MIX

#ifndef ANDROID
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#else
#include <SDL.h>
#include <SDL_mixer.h>
#endif

#include "exception.h"

class ChompSdlMixerException : public ChompException
{
public:
    ChompSdlMixerException() : ChompException(Mix_GetError()) { }
    ChompSdlMixerException(const std::string& _msg) : ChompException(_msg) { }
};

#endif
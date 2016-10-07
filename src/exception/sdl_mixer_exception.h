#ifndef CHOMP_EXCEPTION_SDL_MIX
#define CHOMP_EXCEPTION_SDL_MIX

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "exception.h"

class ChompSdlMixerException : public ChompException
{
public:
    ChompSdlMixerException() : ChompException(Mix_GetError()) { }
    ChompSdlMixerException(const std::string& _msg) : ChompException(_msg) { }
};

#endif
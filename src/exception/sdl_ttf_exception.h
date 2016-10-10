#ifndef CHOMP_EXCEPTION_SDL_TTF
#define CHOMP_EXCEPTION_SDL_TTF

#ifndef ANDROID
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#else
#include <SDL.h>
#include <SDL_ttf.h>
#endif

#include "exception.h"

class ChompSdlTtfException : public ChompException
{
public:
    ChompSdlTtfException() : ChompException(TTF_GetError()) { }
    ChompSdlTtfException(const std::string& _msg) : ChompException(_msg) { }
};

#endif
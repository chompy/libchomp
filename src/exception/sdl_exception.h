#ifndef CHOMP_EXCEPTION_SDL
#define CHOMP_EXCEPTION_SDL

#ifndef ANDROID
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "exception.h"

class ChompSdlException : public ChompException
{
public:
    ChompSdlException() : ChompException(SDL_GetError()) { }
    ChompSdlException(const std::string& _msg) : ChompException(_msg) { }
};

#endif
#ifndef CHOMP_EXCEPTION_SDL_TTF
#define CHOMP_EXCEPTION_SDL_TTF

#include "../sdl_includes.h"
#include "exception.h"

class ChompSdlTtfException : public ChompException
{
public:
    ChompSdlTtfException() : ChompException(TTF_GetError()) { }
    ChompSdlTtfException(const std::string& _msg) : ChompException(_msg) { }
};

#endif
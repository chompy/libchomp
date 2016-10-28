#ifndef CHOMP_EXCEPTION_SDL
#define CHOMP_EXCEPTION_SDL

#include "../sdl_includes.h"
#include "exception.h"

class ChompSdlException : public ChompException
{
public:
    ChompSdlException() : ChompException(SDL_GetError()) { }
    ChompSdlException(const std::string& _msg) : ChompException(_msg) { }
};

#endif
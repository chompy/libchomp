#ifndef CHOMP_EXCEPTION_SDL
#define CHOMP_EXCEPTION_SDL

#include "../sdl_includes.h"
#include "exception.h"

/**
 * Exception that is thrown as a result of a
 * SDL error.
 */
class ChompSdlException : public ChompException
{
public:

    /**
     * Constructor.
     * @see SDL_GetError()
     * Passes exception message from SDL_GetError()
     */
    ChompSdlException() : ChompException(SDL_GetError()) { }

    /**
     * Constructor.
     * @param _msg Exception message
     */    
    ChompSdlException(const std::string& _msg) : ChompException(_msg) { }
    
};

#endif
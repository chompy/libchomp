#ifndef CHOMP_EXCEPTION_SDL_MIX
#define CHOMP_EXCEPTION_SDL_MIX

#include "../sdl_includes.h"
#include "exception.h"

/**
 * Exception that is thrown as a result of a
 * SDL Mixer error.
 */
class ChompSdlMixerException : public ChompException
{
public:

    /**
     * Constructor.
     * @see Mix_GetError()
     * Passes exception message from Mix_GetError()
     */
    ChompSdlMixerException() : ChompException(Mix_GetError()) { }

    /**
     * Constructor.
     * @param _msg Exception message
     */
    ChompSdlMixerException(const std::string& _msg) : ChompException(_msg) { }
    
};

#endif
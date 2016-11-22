#ifndef CHOMP_EXCEPTION_SDL_TTF
#define CHOMP_EXCEPTION_SDL_TTF

#include "../sdl_includes.h"
#include "exception.h"

/**
 * Exception that is thrown as a result of a
 * SDL TTF error.
 */
class ChompSdlTtfException : public ChompException
{
public:

    /**
     * Constructor.
     * @see TTF_GetError()
     * Passes exception message from TTF_GetError()
     */    
    ChompSdlTtfException() : ChompException(TTF_GetError()) { }

    /**
     * Constructor.
     * @param _msg Exception message
     */ 
    ChompSdlTtfException(const std::string& _msg) : ChompException(_msg) { }

};

#endif
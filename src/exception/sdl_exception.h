#ifndef CHOMP_EXCEPTION_SDL
#define CHOMP_EXCEPTION_SDL

#include "../sdl_includes.h"
#include "exception.h"

namespace Chomp
{

    /**
     * Exception that is thrown as a result of a
     * SDL error.
     */
    class SdlException : public Chomp::Exception
    {
    public:

        /**
         * Constructor.
         * @see SDL_GetError()
         * Passes exception message from SDL_GetError()
         */
        SdlException() : Chomp::Exception(SDL_GetError()) { }

        /**
         * Constructor.
         * @param _msg Exception message
         */    
        SdlException(const std::string& _msg) : Chomp::Exception(_msg) { }
        
    };
}

#endif
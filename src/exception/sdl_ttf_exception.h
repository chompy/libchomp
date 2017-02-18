#ifndef CHOMP_EXCEPTION_SDL_TTF
#define CHOMP_EXCEPTION_SDL_TTF

#include "../sdl_includes.h"
#include "exception.h"

namespace Chomp
{

    /**
     * Exception that is thrown as a result of a
     * SDL TTF error.
     */
    class SdlTtfException : public Chomp::Exception
    {
    public:

        /**
         * Constructor.
         * @see TTF_GetError()
         * Passes exception message from TTF_GetError()
         */    
        SdlTtfException() : Chomp::Exception(TTF_GetError()) { }

        /**
         * Constructor.
         * @param _msg Exception message
         */ 
        SdlTtfException(const std::string& _msg) : Chomp::Exception(_msg) { }

    };
};

#endif
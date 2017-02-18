#ifndef CHOMP_EXCEPTION_SDL_MIX
#define CHOMP_EXCEPTION_SDL_MIX

#include "../sdl_includes.h"
#include "exception.h"

namespace Chomp
{

    /**
     * Exception that is thrown as a result of a
     * SDL Mixer error.
     */
    class SdlMixerException : public Chomp::Exception
    {
    public:

        /**
         * Constructor.
         * @see Mix_GetError()
         * Passes exception message from Mix_GetError()
         */
        SdlMixerException() : Chomp::Exception(Mix_GetError()) { }

        /**
         * Constructor.
         * @param _msg Exception message
         */
        SdlMixerException(const std::string& _msg) : Chomp::Exception(_msg) { }
        
    };
};

#endif
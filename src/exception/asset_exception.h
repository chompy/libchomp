#ifndef CHOMP_EXCEPTION_ASSET
#define CHOMP_EXCEPTION_ASSET

#include "../sdl_includes.h"
#include "exception.h"

namespace Chomp
{

    /**
     * Exception that is thrown when asset
     * loading fails.
     */
    class AssetException : public Chomp::Exception
    {
    public:

        /**
         * Constructor.
         * _msg Exception message.
         */
        AssetException(const std::string& _msg) : Chomp::Exception(_msg) { }
        
    };
    
};

#endif
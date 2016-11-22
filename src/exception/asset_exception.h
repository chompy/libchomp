#ifndef CHOMP_EXCEPTION_ASSET
#define CHOMP_EXCEPTION_ASSET

#include "../sdl_includes.h"
#include "exception.h"

/**
 * Exception that is thrown when asset
 * loading fails.
 */
class ChompAssetException : public ChompException
{
public:

    /**
     * Constructor.
     * _msg Exception message.
     */
    ChompAssetException(const std::string& _msg) : ChompException(_msg) { }
    
};

#endif
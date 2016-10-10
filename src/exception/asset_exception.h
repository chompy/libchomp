#ifndef CHOMP_EXCEPTION_ASSET
#define CHOMP_EXCEPTION_ASSET

#ifndef ANDROID
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "exception.h"

class ChompAssetException : public ChompException
{
public:
    ChompAssetException(const std::string& _msg) : ChompException(_msg) { }
};

#endif
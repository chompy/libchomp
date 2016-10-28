#ifndef CHOMP_EXCEPTION_ASSET
#define CHOMP_EXCEPTION_ASSET

#include "../sdl_includes.h"
#include "exception.h"

class ChompAssetException : public ChompException
{
public:
    ChompAssetException(const std::string& _msg) : ChompException(_msg) { }
};

#endif
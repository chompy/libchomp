#ifndef CHOMP_EXCEPTION_MISSINGLIB
#define CHOMP_EXCEPTION_MISSINGLIB

#ifndef ANDROID
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "exception.h"

class ChompMissingLibraryException : public ChompException
{
public:
    ChompMissingLibraryException(const std::string& _msg) : ChompException(_msg) { }
};

#endif
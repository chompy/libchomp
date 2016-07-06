#include "chomp.h"

Chomp::Chomp()
{

    // init sdl systems
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_LogMessage(
            SDL_LOG_CATEGORY_APPLICATION,
            SDL_LOG_PRIORITY_CRITICAL,
            "Unable to init SDL2 video. REASON: %s",
            SDL_GetError()
        );
        return;
    }

}

Chomp::~Chomp()
{

}


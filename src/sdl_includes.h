#ifndef CHOMP_SDL_INCLUDES_H
#define CHOMP_SDL_INCLUDES_H

#if defined(ANDROID) || defined(EMSCRIPTEN)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#ifndef WITHOUT_SDL_TTF
#if defined(ANDROID) || defined(EMSCRIPTEN)
#include <SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif
#include "exception/sdl_ttf_exception.h"
#endif

#ifndef WITHOUT_SDL_MIXER
#if defined(ANDROID) || defined(EMSCRIPTEN)
#include <SDL_mixer.h>
#else
#include <SDL2/SDL_mixer.h>
#endif
#include "exception/sdl_mixer_exception.h"
#endif

#ifndef WITHOUT_SDL_IMAGE
#if defined(ANDROID) || defined(EMSCRIPTEN)
#include <SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif
#endif

#endif
/**
    This file is part of Libchomp.

    Libchomp is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Libchomp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Libchomp.  If not, see <http://www.gnu.org/licenses/>.
**/

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
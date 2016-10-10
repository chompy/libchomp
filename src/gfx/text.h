#ifndef CHOMP_GFX_TEXT_H
#define CHOMP_GFX_TEXT_H

#ifndef ANDROID
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#ifndef WITHOUT_SDL_TTF
#ifndef ANDROID
#include <SDL2/SDL_ttf.h>
#else
#include <SDL_ttf.h>
#include "../exception/sdl_ttf_exception.h"
#endif
#else

#include <vector>
#include <string>
#include "layer.h"
#include "../exception/sdl_exception.h"
#include "../exception/missing_library_exception.h"
#include <iostream>

class ChompGfxText : public ChompGfxLayer
{
public:

    ChompGfxText(SDL_Renderer* _renderer, char* fontData, uint32_t fontDataSize, uint16_t fontPtSize, ChompGfxSize* _size) : ChompGfxLayer(_renderer, NULL, _size)
    {
        font = NULL;
        setFont(fontData, fontDataSize, fontPtSize);
    }
    ~ChompGfxText();

protected:

    TTF_Font* font;

    void setFont(uint8_t* fontData, uint32_t fontDataSize, uint16_t fontPtSize);

};
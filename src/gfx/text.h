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
#endif
#include "../exception/sdl_ttf_exception.h"
#endif

#include <vector>
#include <string>
#include "layer.h"
#include "../exception/sdl_exception.h"
#include <iostream>

#define TEXT_LEFT 0
#define TEXT_CENTER 1
#define TEXT_RIGHT 2
#define TEXT_TOP 0
#define TEXT_MIDDLE 1
#define TEXT_BOTTOM 2

class ChompGfxText : public ChompGfxLayer
{
public:

    static char FONT_ASSET_PREFIX[];

    ChompGfxText(SDL_Renderer* _renderer, uint8_t* fontData, uint32_t fontDataSize, uint16_t fontPtSize, ChompGfxSize* _size) : ChompGfxLayer(_renderer, NULL, _size)
    {
        font = NULL;
        setFont(fontData, fontDataSize, fontPtSize);
    }
    ~ChompGfxText();

    void setText(const char* text, uint8_t hAlign, uint8_t vAlign);

protected:

    #ifndef WITHOUT_SDL_TTF
    TTF_Font* font;
    #else
    void* font;
    #endif

    void setFont(uint8_t* fontData, uint32_t fontDataSize, uint16_t fontPtSize);
    void buildTexture();

};

#endif
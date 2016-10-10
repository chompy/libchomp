#include "text.h"

ChompGfxText::~ChompGfxText()
{
    if (font) {
        TTF_CloseFont(font);
    }
}

ChompGfxText::setFont(uint8_t* fontData, uint32_t fontDataSize, uint16_t fontPtSize)
{
    #ifndef WITHOUT_SDL_TTF
    SDL_RWops* fontDataRW = SDL_RWFromMem(&fontData, fontDataSize);
    if (!fontDataRW) {
        throw ChompSdlException();
    }
    font = TTF_OpenFontRW(fontDataRW, 1, fontPtSize);
    if (!font) {
        throw ChompSdlTtfException();
    }
    #else
        throw ChompMissingLibraryException("Cannot load fonts without SDL2 TTF library.");
    #endif
}
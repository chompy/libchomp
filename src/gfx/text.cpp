#include "text.h"

char ChompGfxText::FONT_ASSET_PREFIX[] = "font_";

ChompGfxText::~ChompGfxText()
{
    if (font) {
        TTF_CloseFont(font);
    }
}

void ChompGfxText::setFont(uint8_t* fontData, uint32_t fontDataSize, uint16_t fontPtSize)
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
    #endif
}

void ChompGfxText::setText(const char* text, uint8_t hAlign, uint8_t vAlign)
{

    // wipe layer
    uint8_t r,g,b,a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    fill();
    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    // draw text
    #ifndef WITHOUT_SDL_TTF
    SDL_Color color = {r, g, b};
    SDL_Surface* textSurface = TTF_RenderUTF8_Blended(
        font,
        text,
        color
    );
    if (!textSurface) {
        throw ChompSdlTtfException();
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(
        renderer,
        textSurface
    );
    if (!textTexture) {
        throw ChompSdlException();
    }
    SDL_FreeSurface(textSurface);
    SDL_SetRenderTarget(renderer, texture);
    // todo calculate position
    SDL_RenderCopy(
        renderer,
        textTexture,
        NULL,
        NULL
    );
    SDL_DestroyTexture(textTexture);
    #endif

}
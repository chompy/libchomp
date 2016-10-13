#include "text.h"

char ChompGfxText::FONT_ASSET_PREFIX[] = "font_";

ChompGfxText::~ChompGfxText()
{
    if (font) {
        TTF_CloseFont(font);
    }
}

void ChompGfxText::setFont(uint8_t* fontData, const uint32_t fontDataSize, const uint16_t fontPtSize)
{
    #ifndef WITHOUT_SDL_TTF
    SDL_RWops* fontDataRW = SDL_RWFromMem(&fontData[0], fontDataSize);
    if (!fontDataRW) {
        throw ChompSdlException();
    }
    font = TTF_OpenFont("assets/font/impact.ttf", fontPtSize);
    //font = TTF_OpenFontRW(fontDataRW, 1, fontPtSize);
    if (!font) {
        throw ChompSdlTtfException();
    }
    #endif
}

void ChompGfxText::setText(const char* text)
{
    setText(text, TEXT_LEFT, TEXT_TOP);
}

void ChompGfxText::setText(const char* text, uint8_t hAlign)
{
    setText(text, hAlign, TEXT_TOP);
}

void ChompGfxText::setText(const char* text, uint8_t hAlign, uint8_t vAlign)
{
    if (!font) {
        return;
    }

    // get current color
    uint8_t r,g,b,a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_Color color = {r, g, b, a};

    // change color to wipe texture
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderFillRect(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    // no need to proceed if text was not provided
    if (!text) {
        return;
    }

    #ifndef WITHOUT_SDL_TTF 
    // create texture surface
    // @TODO option to use other render methods
    SDL_Surface* textSurface = TTF_RenderUTF8_Solid(
        font,
        text,
        color
    );
    if (!textSurface) {
        throw ChompSdlTtfException();
    }

    // convert to texture
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(
        renderer,
        textSurface
    );
    if (!textTexture) {
        throw ChompSdlException();
    }
    SDL_Rect destRect = {0, 0, textSurface->w, textSurface->h}; 
    SDL_FreeSurface(textSurface);

    // alignment
    switch (hAlign) {
        case TEXT_CENTER:
        {
            destRect.x = (getPixelWidth() / 2) - (textSurface->w / 2);
            break;
        }
        case TEXT_RIGHT:
        {
            destRect.x = getPixelWidth() - textSurface->w;
            break;
        }
    }
    switch (vAlign) {
        case TEXT_MIDDLE:
        {
            destRect.y = (getPixelHeight() / 2) - (textSurface->h / 2);
            break;
        }
        case TEXT_BOTTOM:
        {
            destRect.y = getPixelHeight() - textSurface->h;
            break;
        }
    }

    // draw to layer
    if (
        SDL_RenderCopy(
            renderer,
            textTexture,
            NULL,
            &destRect
        ) != 0
    ) {
        throw ChompSdlException();
    }
    
    SDL_DestroyTexture(textTexture);
    #endif

}
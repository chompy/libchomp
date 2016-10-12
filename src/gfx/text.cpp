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
    //font = TTF_OpenFont("assets/font/ariali.ttf", fontPtSize);
    font = TTF_OpenFontRW(fontDataRW, 1, fontPtSize);
    if (!font) {
        throw ChompSdlTtfException();
    }
    #endif
}

void ChompGfxText::buildTexture()
{
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        512, // @TODO allow user to set
        512        
    );
    if (!texture) {
        throw ChompSdlException();
    }
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    setPixelSize();
}

void ChompGfxText::setText(const char* text, uint8_t hAlign, uint8_t vAlign)
{
    if (!font) {
        return;
    }

    buildTexture();
    ChompGfxRect testRect;
    testRect.x = .9;
    testRect.y = 0;
    testRect.w = 1;
    testRect.h = 1;
    drawFillRect(&testRect);

    // draw text
    #ifndef WITHOUT_SDL_TTF
    uint8_t r,g,b,a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_Color color = {r, g, b, a};
    SDL_Surface* textSurface = TTF_RenderText_Blended(
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

    SDL_Rect destRect = {0, 0, textSurface->w, textSurface->h}; 
    SDL_FreeSurface(textSurface);



    SDL_SetRenderTarget(renderer, texture);
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
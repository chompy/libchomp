#include "text.h"

char ChompGfxText::FONT_ASSET_PREFIX[] = "font_";

ChompGfxText::~ChompGfxText()
{
    if (font) {
        TTF_CloseFont(font);
    }
    if (fontDataRW) {
        SDL_RWclose(fontDataRW);
    }
    if (fontData) {
        delete fontData;
    }
}

void ChompGfxText::setFont(uint8_t* _fontData, const uint32_t fontDataSize, const uint16_t fontPtSize)
{
    #ifndef WITHOUT_SDL_TTF
    if (font) {
        TTF_CloseFont(font);
    }
    if (fontDataRW) {
        SDL_RWclose(fontDataRW);
    }
    if (fontData) {
        delete fontData;
    }
    fontData = new uint8_t[fontDataSize];
    memcpy(fontData, _fontData, fontDataSize);
    fontDataRW = SDL_RWFromMem(&fontData[0], fontDataSize);
    if (!fontDataRW) {
        throw ChompSdlException();
    }
    //font = TTF_OpenFont("assets/font/tahoma.ttf", fontPtSize);
    font = TTF_OpenFontRW(fontDataRW, 0, fontPtSize);
    if (!font) {
        throw ChompSdlTtfException();
    }
    setText("");
    #endif
}

std::vector<std::string> ChompGfxText::getLines(const char* text)
{
    std::vector<std::string> lines;
    if (!text || !font) {
        return lines;
    }
    std::string line;
    int w;
    for(uint16_t i = 0; i < strlen(text); i++) {
        // null terminator
        if (text[i] == '\0') {
            break;
        }
        // get current line size
        TTF_SizeText(font, line.c_str(), &w, NULL);
        // new line
        if (text[i] == '\n' || w > getPixelWidth()) {
            lines.push_back(line);
            line.clear();
            continue;
        }
        // add char to line
        line.push_back(text[i]);
    }
    if (!line.empty()) {
        lines.push_back(line);
    }
    return lines;
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
    if (!text || strlen(text) == 0) {
        return;
    }

    #ifndef WITHOUT_SDL_TTF
    // get lines
    std::vector<std::string> lines = getLines(text);
    uint16_t lineY = 0;

    // iterate lines
    for (uint16_t i = 0; i < lines.size(); i++) {
        std::string line = lines[i];

        // create texture surface
        // @TODO option to use other render methods
        SDL_Surface* textSurface = TTF_RenderText_Blended(
            font,
            line.c_str(),
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
        SDL_Rect destRect = {0, lineY, textSurface->w, textSurface->h}; 
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

        // next line
        lineY += destRect.h;
    }
    #endif

}
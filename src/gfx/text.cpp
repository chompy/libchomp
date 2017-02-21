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

#include "text.h"

char Chomp::GfxText::FONT_ASSET_PREFIX[] = "font_";

Chomp::GfxText::~GfxText()
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

void Chomp::GfxText::setFont(uint8_t* _fontData, const uint32_t fontDataSize, const uint16_t fontPtSize)
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
        throw Chomp::SdlException();
    }
    font = TTF_OpenFontRW(fontDataRW, 0, fontPtSize);
    if (!font) {
        throw Chomp::SdlTtfException();
    }
    setText("");
    #endif
}

std::vector<std::string> Chomp::GfxText::getLines(const char* text)
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

void Chomp::GfxText::setText(const char* text)
{
    setText(text, CHOMP_GFX_TEXT_LEFT, CHOMP_GFX_TEXT_TOP);
}

void Chomp::GfxText::setText(const char* text, uint8_t hAlign)
{
    setText(text, hAlign, CHOMP_GFX_TEXT_TOP);
}

void Chomp::GfxText::setText(const char* text, uint8_t hAlign, uint8_t vAlign)
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
            throw Chomp::SdlTtfException();
        }

        // convert to texture
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(
            renderer,
            textSurface
        );
        if (!textTexture) {
            throw Chomp::SdlException();
        }
        SDL_Rect destRect = {0, lineY, textSurface->w, textSurface->h}; 
        SDL_FreeSurface(textSurface);

        // alignment
        switch (hAlign) {
            case CHOMP_GFX_TEXT_CENTER:
            {
                destRect.x = (getPixelWidth() / 2) - (textSurface->w / 2);
                break;
            }
            case CHOMP_GFX_TEXT_RIGHT:
            {
                destRect.x = getPixelWidth() - textSurface->w;
                break;
            }
        }
        switch (vAlign) {
            case CHOMP_GFX_TEXT_MIDDLE:
            {
                destRect.y = (getPixelHeight() / 2) - (textSurface->h / 2);
                break;
            }
            case CHOMP_GFX_TEXT_BOTTOM:
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
            throw Chomp::SdlException();
        }
        SDL_DestroyTexture(textTexture);

        // next line
        lineY += destRect.h;
    }
    #endif

}
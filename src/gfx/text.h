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

#ifndef CHOMP_GFX_TEXT_H
#define CHOMP_GFX_TEXT_H

#include <vector>
#include <string>
#include "layer.h"
#include "../exception/sdl_exception.h"

#define CHOMP_GFX_TEXT_LEFT 0
#define CHOMP_GFX_TEXT_CENTER 1
#define CHOMP_GFX_TEXT_RIGHT 2
#define CHOMP_GFX_TEXT_TOP 0
#define CHOMP_GFX_TEXT_MIDDLE 1
#define CHOMP_GFX_TEXT_BOTTOM 2

namespace Chomp
{

    /**
     * Text layer capable of rendering text.
     */
    class GfxText : public Chomp::GfxLayer
    {
    public:

        /**
         * Font asset prefix.
         */
        static char FONT_ASSET_PREFIX[];

        /**
         * Constructor.
         * @param _renderer SDL Renderer
         * @param _fontData Byte array containing font data
         * @param fontDataSize Length of font data
         * @param fontPtSize Point size of font
         * @param _texture SDL Texture to draw to
         * @param _size Size of layer
         */
        GfxText(
            SDL_Renderer* _renderer,
            uint8_t* _fontData,
            const uint32_t fontDataSize,
            const uint16_t fontPtSize,
            SDL_Texture* _texture,
            Chomp::GfxSize* _size
        ) : Chomp::GfxLayer(_renderer, _texture, _size)
        {
            fontData = NULL;
            fontDataRW = NULL;
            font = NULL;
            setFont(_fontData, fontDataSize, fontPtSize);
        }

        /**
         * Destructor.
         */
        ~GfxText();

        /**
         * Draw given text to layer.
         * @param text Char array containing text
         */
        void setText(const char* text);

        /**
         * Draw given text to layer.
         * @param text Char array containing text
         * @param hAlign Horizontal alignment
         */
        void setText(const char* text, const uint8_t hAlign);

        /**
         * Draw given text to layer.
         * @param text Char array containing text
         * @param hAlign Horizontal alignment
         * @param vAlign Vertical alignment
         */
        void setText(const char* text, const uint8_t hAlign, const uint8_t vAlign);

    protected:

        /**
         * Byte array containing font data.
         */
        uint8_t* fontData;

        /**
         * SDL RWops pointed at font data.
         */
        SDL_RWops* fontDataRW;

        #ifndef WITHOUT_SDL_TTF

        /**
         * SDL TTF Font 
         */
        TTF_Font* font;

        #else

        /**
         * Null font pointer.
         */
        void* font;

        #endif

        /**
         * Set current font.
         * @param _fontData Font data byte array
         * @param fontDataSize Byte size of font data
         * @param fontPtSize Point size of font
         */
        void setFont(uint8_t* _fontData, const uint32_t fontDataSize, const uint16_t fontPtSize);

        /**
         * Split given text string in to vector containing
         * each line.
         * @param text Char array containing text string
         * @return Vector containing each line
         */
        std::vector<std::string> getLines(const char* text);

    };
};

#endif
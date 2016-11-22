#ifndef CHOMP_GFX_TEXT_H
#define CHOMP_GFX_TEXT_H

#include <vector>
#include <string>
#include "layer.h"
#include "../exception/sdl_exception.h"

#define TEXT_LEFT 0
#define TEXT_CENTER 1
#define TEXT_RIGHT 2
#define TEXT_TOP 0
#define TEXT_MIDDLE 1
#define TEXT_BOTTOM 2

/**
 * Text layer capable of rendering text.
 */
class ChompGfxText : public ChompGfxLayer
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
     * @param fontPtSize Point size of font
     * @param _texture SDL Texture to draw to
     * @param _size Size of layer
     */
    ChompGfxText(
        SDL_Renderer* _renderer,
        uint8_t* _fontData,
        const uint32_t fontDataSize,
        const uint16_t fontPtSize,
        SDL_Texture* _texture,
        ChompGfxSize* _size
    ) : ChompGfxLayer(_renderer, _texture, _size)
    {
        fontData = NULL;
        fontDataRW = NULL;
        font = NULL;
        setFont(_fontData, fontDataSize, fontPtSize);
    }

    /**
     * Destructor.
     */
    ~ChompGfxText();

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

#endif
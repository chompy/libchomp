#ifndef CHOMP_GFX_LAYER_H
#define CHOMP_GFX_LAYER_H

#include <iostream>
#include "../sdl_includes.h"
#include "structs.h"

/**
 * A layer to render graphics on to.
 */
class ChompGfxLayer
{
public:

    /**
     * Constructor.
     * _renderer SDL renderer
     * _texture SDL texture to draw to
     * _size Size of layer
     */
    ChompGfxLayer(SDL_Renderer* _renderer, SDL_Texture* _texture, ChompGfxSize* _size);

    /**
     * Destructor.
     */
    virtual ~ChompGfxLayer();

    /**
     * SDL texture to render to.
     */
    SDL_Texture* texture;

    /**
     * Size to render layer at in
     * the relative coordinate system.    
     */
    ChompGfxSize size;

    /**
     * Defines render order.
     */
    int16_t zIndex;

    /**
     * Rotation of layer.
     */
    float rotation;

    /**
     * Flip layer. See structs.h for
     * constants defines flip behavior.
     */ 
    uint8_t flip;

    /**
     * Convert relative size to pixel size relative to
     * to the pixel size of this layer.
     * @param _size Relative size to convert
     * @param w Filled with pixel width
     * @param h Filled with pixel height
     */
    void toPixels(ChompGfxSize* _size, uint16_t* w, uint16_t* h);

    /**
     * Convert relative position to pixel position relative to
     * to the pixel size of this layer.
     * @param _pos Relative position to convert
     * @param x Filled with pixel x
     * @param y Filled with pixel y
     */    
    void toPixels(ChompGfxPosition* _pos, uint16_t* x, uint16_t* y);

    /**
     * Convert relative rect to pixels relative to
     * to the pixel size of this layer.
     * @param _rect Rect
     * @param x Filled with pixel x
     * @param y Filled with pixel y
     * @param w Filled with pixel width
     * @param h Filled with pixel height
     */    
    void toPixels(ChompGfxRect* _rect, uint16_t* x, uint16_t* y, uint16_t* w, uint16_t* h);

    /**
     * Convert given pixel width and height to relative
     * coordinate pixel size in this layer.
     * @param w pixel width
     * @param h pixel height
     * @return Struct with relative size
     */    
    ChompGfxSize getPixelSize(const uint16_t w, const uint16_t h);

    /**
     * Convert given pixel x and y to relative
     * coordinate pixel position in this layer.
     * @param x pixel x
     * @param y pixel y
     * @return Struct with relative position
     */
    ChompGfxPosition getPixelPosition(const uint16_t x, const uint16_t y);

    /**
     * Get pixel width of layer.
     * @return Pixel width
     */
    uint16_t getPixelWidth() { return pixelWidth; }

    /**
     * Get pixel height of layer.
     * @return Pixel height
     */
    uint16_t getPixelHeight() { return pixelHeight; }

    /**
     * Get pixel width of one relative position unit.
     * @return Pixel width
     */
    uint16_t getPixelUnitWidth() { return pixelUnitWidth; }

    /**
     * Get pixel height of one relative position unit.
     * @return Pixel height
     */
    uint16_t getPixelUnitHeight() { return pixelUnitHeight; }

    /**
     * Compare two rects for collision.
     * @param rect1 Rect one
     * @param rect2 Rect two
     * @return True if rects have collided
     */
    static bool hasCollision(ChompGfxRect* rect1, ChompGfxRect* rect2);

    /**
     * Check if this layer at given position has 
     * collision with given rect.
     * @param pos1 Defined position of layer
     * @param rect2 Rect to test
     * @return True if rect has collided
     */
    bool hasCollision(ChompGfxPosition* pos1, ChompGfxRect* rect2);

    /**
     * Compare two layers for collision at given positions.
     * @param pos1 Position of layer one
     * @param layer2 Layer two
     * @param pos2 Position of layer two
     * @return True if layers have collided
     */
    bool hasCollision(ChompGfxPosition* pos1, ChompGfxLayer* layer2, ChompGfxPosition* pos2);

    /**
     * Fill layer with current draw color.
     * @see ChompGfx::setDrawColor
     */
    void fill();

    /**
     * Draw a line with current draw color.
     * @see ChompGfx::setDrawColor
     * @param pos1 Starting point of line
     * @param pos2 Ending point of line
     */
    void drawLine(ChompGfxPosition* pos1, ChompGfxPosition* pos2);

    /**
     * Draw a rect with current draw color.
     * @see ChompGfx::setDrawColor
     * @param rect Rect to draw
     */
    void drawRect(ChompGfxRect* rect);

    /**
     * Draw a filled rect with current draw color.
     * @see ChompGfx::setDrawColor
     * @param rect Rect to draw
     */
    void drawFillRect(ChompGfxRect* rect);

    /**
     * Render another layer on to this layer.
     * @param layer Layer to render
     * @param srcRect Section of layer to render
     * @param dstRect Section of this layer to render to
     */    
    void drawLayer(ChompGfxLayer* layer, ChompGfxRect* srcRect, ChompGfxRect* dstRect);
    
    /**
     * Render a layer on to another layer.
     * @param renderer SDL Renderer
     * @param srcLayer Source layer
     * @param dstLayer Destination layer
     * @param srcRect Section of source layer to render
     * @param dstRect Section of destination layer to render to
     */
    static void drawLayerToLayer(SDL_Renderer* renderer, ChompGfxLayer* srcLayer, ChompGfxLayer* dstLayer, ChompGfxRect* srcRect, ChompGfxRect* dstRect);

    /**
     * Draw given layer to current SDL render target.
     * @param renderer SDL Renderer
     * @param srcLayer Section of source layer to render
     * @param dstLayer Section of render target to render to
     * @param targetUnitWidth Pixel unit width of target
     * @param targetUnitHeight Pixel unit height of target
     */
    static void drawLayerToRenderTarget(SDL_Renderer* renderer, ChompGfxLayer* srcLayer, ChompGfxRect* srcRect, ChompGfxRect* dstRect, uint16_t targetUnitWidth, uint16_t targetUnitHeight);

protected:

    /**
     * SDL Renderer
     */
    SDL_Renderer* renderer;

    /**
     * Pixel width of layer.
     */
    uint16_t pixelWidth;

    /**
     * Pixel height of layer.
     */
    uint16_t pixelHeight;

    /**
     * Pixel width of one unit for this layer.
     */
    uint16_t pixelUnitWidth;

    /**
     * Pixel height of one unit for this layer.
     */
    uint16_t pixelUnitHeight;

    /**
     * Calculate pixel unit sizes from pixel
     * size of layer's SDL Texture.
     */
    void setPixelSize();

};

#endif
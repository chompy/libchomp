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

#ifndef CHOMP_GFX_LAYER_H
#define CHOMP_GFX_LAYER_H

#include <iostream>
#include "../sdl_includes.h"
#include "structs.h"

namespace Chomp
{

    /**
     * A layer to render graphics on to.
     */
    class GfxLayer
    {
    public:

        /**
         * Constructor.
         * _renderer SDL renderer
         * _texture SDL texture to draw to
         */
        GfxLayer(SDL_Renderer* _renderer, SDL_Texture* _texture);

        /**
         * Destructor.
         */
        virtual ~GfxLayer();

        /**
         * SDL texture to render to.
         */
        SDL_Texture* texture;

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
         * Get pixel size of layer.
         * @return Layer size
         */
        Chomp::GfxSize getSize();

        /**
         * Compare two rects for collision.
         * @param rect1 Rect one
         * @param rect2 Rect two
         * @return True if rects have collided
         */
        static bool hasCollision(Chomp::GfxRect* rect1, Chomp::GfxRect* rect2);

        /**
         * Check if this layer at given position has 
         * collision with given rect.
         * @param pos1 Defined position of layer
         * @param rect2 Rect to test
         * @return True if rect has collided
         */
        bool hasCollision(Chomp::GfxPosition* pos1, Chomp::GfxRect* rect2);

        /**
         * Compare two layers for collision at given positions.
         * @param pos1 Position of layer one
         * @param layer2 Layer two
         * @param pos2 Position of layer two
         * @return True if layers have collided
         */
        bool hasCollision(Chomp::GfxPosition* pos1, Chomp::GfxLayer* layer2, Chomp::GfxPosition* pos2);

        /**
         * Fill layer with current draw color.
         * @see Chomp::Gfx::setDrawColor
         */
        void fill();

        /**
         * Draw a line with current draw color.
         * @see Chomp::Gfx::setDrawColor
         * @param pos1 Starting point of line
         * @param pos2 Ending point of line
         */
        void drawLine(Chomp::GfxPosition* pos1, Chomp::GfxPosition* pos2);

        /**
         * Draw a rect with current draw color.
         * @see Chomp::Gfx::setDrawColor
         * @param rect Rect to draw
         */
        void drawRect(Chomp::GfxRect* rect);

        /**
         * Draw a filled rect with current draw color.
         * @see Chomp::Gfx::setDrawColor
         * @param rect Rect to draw
         */
        void drawFillRect(Chomp::GfxRect* rect);

        /**
         * Render another layer on to this layer.
         * @param layer Layer to render
         * @param srcRect Section of layer to render
         * @param dstRect Section of this layer to render to
         */    
        void drawLayer(Chomp::GfxLayer* layer, Chomp::GfxRect* srcRect, Chomp::GfxRect* dstRect);
        
        /**
         * Render a layer on to another layer.
         * @param renderer SDL Renderer
         * @param srcLayer Source layer
         * @param dstLayer Destination layer
         * @param srcRect Section of source layer to render
         * @param dstRect Section of destination layer to render to
         */
        static void drawLayerToLayer(SDL_Renderer* renderer, Chomp::GfxLayer* srcLayer, Chomp::GfxLayer* dstLayer, Chomp::GfxRect* srcRect, Chomp::GfxRect* dstRect);

        /**
         * Draw given layer to current SDL render target.
         * @param renderer SDL Renderer
         * @param srcLayer Section of source layer to render
         * @param dstLayer Section of render target to render to
         */
        static void drawLayerToRenderTarget(SDL_Renderer* renderer, Chomp::GfxLayer* srcLayer, Chomp::GfxRect* srcRect, Chomp::GfxRect* dstRect);

    protected:

        /**
         * SDL Renderer
         */
        SDL_Renderer* renderer;

    };
};

#endif
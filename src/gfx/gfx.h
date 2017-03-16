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

#ifndef CHOMP_GFX_H
#define CHOMP_GFX_H

#include <vector>
#include <algorithm>
#include <stdint.h>
#include <string>
#include "../sdl_includes.h"
#include "../asset/asset.h"
#include "../asset/bitmap.h"
#include "structs.h"
#include "layer.h"
#include "sprite.h"
#include "text.h"
#include "grid.h"
#include "../exception/sdl_exception.h"

#define CHOMP_GFX_DEFAULT_WINDOW_W 640
#define CHOMP_GFX_DEFAULT_WINDOW_H 480
#define CHOMP_GFX_DEFAULT_LAYER_PIXEL_SIZE 512

namespace Chomp
{

    /**
     * Contains data on how to render a
     * single layer.
     */
    struct RenderLayers {
        bool operator<(const RenderLayers &renderLayer) const { return renderLayer.layer->zIndex > layer->zIndex; }
        Chomp::GfxLayer* layer; /**< Layer to render >*/
        Chomp::GfxRect srcRect; /**< Section of layer to render >*/
        Chomp::GfxRect dstRect; /**< Section of renderer to render layer on to >*/
    };

    /**
     * Main graphic rendering class.
     */
    class Gfx
    {
    public:

        /**
         * Constructor.
         */
        Gfx();

        /**
         * Destructor.
         */
        ~Gfx();

        /**
         * Get pixel size of window
         * @return Struct containing window size
         */
        Chomp::GfxSize getWindowSize();

        /**
         * Set the title of the graphic window.
         * @param title Char array containing title
         */
        void setWindowTitle(const char* title);

        /**
         * Get pixel position of camera
         * @return Struct with camera coordinates
         */
        Chomp::GfxPosition getCameraPosition();

        /**
         * Set position of camera with relative coordinate
         * system.
         * @param position Struct containing desired position
         */
        void setCameraPosition(Chomp::GfxPosition* position);

        /**
         * Set render draw color. Used to draw primatives
         * and text.
         * @param color Struct containing color
         */
        void setDrawColor(Chomp::GfxColor* color);

        /**
         * Set mouse cusor visibility.
         * @param stage Cursor visible if true
         */
        void setCursorVisibility(bool state);

        /**
         * Create a render layer.
         * @param size Struct containing desired size
         * @return Pointer to layer
         */
        Chomp::GfxLayer* newLayer(Chomp::GfxSize* size);

        /**
         * Create a render layer from bitmap data.
         * @param bitmap Bitmap data
         * @param frame Bitmap frame
         * @return Pointer to layer
         */
        Chomp::GfxLayer* newLayerFromBitmap(uint8_t* bitmap, const uint16_t frame);

        /**
         * Create a render layer from given sprite file.
         * @param spriteName Char array containing sprite filename
         * @return Pointer to layer
         */
        Chomp::GfxSprite* newSprite(const char* spriteName);

        /**
         * Create a text render layer for displaying text
         * of a given font.
         * @param fontName Char array containing font filename
         * @param ptSize Point size of font
         * @param Struct containing desired size of layer
         * @return Pointer to layer
         */
        Chomp::GfxText* newTextLayer(const char* fontName, const uint16_t ptSize, Chomp::GfxSize* size);

        /**
         * Add given layer to render queue. The render
         * order is affected by the layer's zIndex value.
         * @param layer Layer to add to queue
         * @param srcRect Section of layer to render
         * @param dstRect Section to render layer to
         */
        void addLayerToRenderer(Chomp::GfxLayer* layer, Chomp::GfxRect* srcRect, Chomp::GfxRect* dstRect);

        /**
         * Render all layers in queue.
         * @see Chomp::Gfx::addLayerToRenderer()
         */
        void render();

    protected:

        /**
         * SDL Window
         */
        SDL_Window* window;

        /**
         * SDL Renderer
         */
        SDL_Renderer* renderer;

        /**
         * Postition of camera.
         */
        Chomp::GfxPosition camera;

        /**
         * Vector containing render layer queue.
         */
        std::vector<RenderLayers> renderLayers;

    };
};

#endif
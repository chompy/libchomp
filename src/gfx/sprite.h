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

#ifndef CHOMP_GFX_SPRITE_H
#define CHOMP_GFX_SPRITE_H

#include <vector>
#include <string>
#include "layer.h"
#include "../asset/bitmap.h"

namespace Chomp
{

    /**
     * Contains data for an animation.
     */
    struct GfxSpriteAnimationData
    {
        std::string name; /**< Name of animation >**/
        std::vector<uint16_t> frames; /**< Vector containing animation frames >**/
    };

    /**
     * Sprite layer capable of rendering animation.
     */
    class GfxSprite : public Chomp::GfxLayer
    {

    public:

        /**
         * Prefix of sprite assets.
         */
        static char SPRITE_ASSET_PREFIX[];

        /**
         * Constructor.
         * @param _renderer SDL Renderer
         * @param bitmap Bitmap data
         */
        GfxSprite(SDL_Renderer* _renderer, uint8_t* bitmap) : Chomp::GfxLayer(_renderer, NULL)
        {
            animationFramerate = 10;
            setTextures(bitmap);
            getAnimationData(bitmap);
            currentAnimation = NULL;
            lastAnimationTick = 0;
            animationIndex = 0;
        }

        /**
         * Destructor.
         */
        ~GfxSprite();

        /**
         * Set frame to draw on next render.
         * @param frame Frame to use
         * @return False if given frame is out of range
         */
        bool setFrame(const uint16_t frame);

        /**
         * Set animation to play.
         * @param name Char array containing name of animation
         * @return True if animation exists
         */
        bool setAnimation(const char* name);

        /**
         * Sets current animation frame based on timing
         * and animation FPS.
         */
        void updateAnimationFrame();

    protected:

        /**
         * Vector containing textures for each
         * sprite frame.
         */
        std::vector<SDL_Texture*> spriteTextures;

        /**
         * Vector containing animation data.
         */
        std::vector<Chomp::GfxSpriteAnimationData> animationData;

        /**
         * Pointer to animation data for currently
         * playing animation.
         */
        Chomp::GfxSpriteAnimationData* currentAnimation;

        /**
         * Frame rate of animation.
         */
        uint16_t animationFramerate;

        /**
         * Last tick animation frame was updated.
         */
        uint32_t lastAnimationTick;

        /**
         * Current animation frame index.
         */
        uint16_t animationIndex;

        /**
         * Convert bitmap frames to SDL textures.
         * @param bitmap Bitmap data
         */
        void setTextures(uint8_t* bitmap);

        /**
         * Get animation data from bitmap.
         * @param bitmap Bitmap data
         */
        void getAnimationData(uint8_t* bitmap);

    };
};

#endif
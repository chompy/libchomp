#ifndef CHOMP_GFX_SPRITE_H
#define CHOMP_GFX_SPRITE_H

#include <vector>
#include <string>
#include "layer.h"
#include "../asset/bitmap.h"

/**
 * Contains data for an animation.
 */
struct ChompGfxSpriteAnimationData
{
    std::string name; /**< Name of animation >**/
    std::vector<uint16_t> frames; /**< Vector containing animation frames >**/
};

/**
 * Sprite layer capable of rendering animation.
 */
class ChompGfxSprite : public ChompGfxLayer
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
     * @param _size Size of layer
     */
    ChompGfxSprite(SDL_Renderer* _renderer, uint8_t* bitmap, ChompGfxSize* _size) : ChompGfxLayer(_renderer, NULL, _size)
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
    ~ChompGfxSprite();

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
    std::vector<ChompGfxSpriteAnimationData> animationData;

    /**
     * Pointer to animation data for currently
     * playing animation.
     */
    ChompGfxSpriteAnimationData* currentAnimation;

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

#endif
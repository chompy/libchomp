#include "sprite.h"
char ChompGfxSprite::SPRITE_ASSET_PREFIX[] = "spr_";

ChompGfxSprite::~ChompGfxSprite()
{
    for (auto &spriteTexture : spriteTextures) {
        SDL_DestroyTexture(spriteTexture);
    }
    spriteTextures.clear();
}

bool ChompGfxSprite::setFrame(uint16_t frame)
{
    if (frame >= spriteTextures.size()) {
        return false;
    }
    texture = spriteTextures[frame];
    return true;
}

void ChompGfxSprite::setTextures(uint8_t* bitmap)
{
    spriteTextures.clear();
    for (uint16_t i = 0; i < ChompBitmap::getFrameCount(bitmap); i++) {
        spriteTextures.push_back(
            ChompBitmap::getTexture(
                renderer,
                bitmap,
                i
            )
        );
    }
    if (setFrame(0)) {
        setPixelSize();
    }
}
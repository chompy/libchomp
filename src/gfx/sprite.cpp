#include "sprite.h"
char ChompGfxSprite::SPRITE_ASSET_PREFIX[] = "spr_";

ChompGfxSprite::~ChompGfxSprite()
{
    for (uint16_t i = 0; i < spriteTextures.size(); i++) {
        SDL_DestroyTexture(spriteTextures[i]);
    }
    spriteTextures.clear();
}

bool ChompGfxSprite::setFrame(const uint16_t frame)
{
    if (frame >= spriteTextures.size()) {
        return false;
    }
    texture = spriteTextures[frame];
    return true;
}

bool ChompGfxSprite::setAnimation(const char* name)
{
    std::string nameString = std::string(name);
    if (currentAnimation && currentAnimation->name == nameString) {
        return true;
    }
    currentAnimation = NULL;
    for (uint16_t i = 0; i < animationData.size(); i++) {
        if (animationData[i].name == nameString) {
            currentAnimation = &animationData[i];
            lastAnimationTick = SDL_GetTicks();
            animationIndex = 0;
            setFrame( currentAnimation->frames[ animationIndex ] );
            return true;
        }
    }
    return false;
}

void ChompGfxSprite::updateAnimationFrame()
{
    if (!currentAnimation) {
        return;
    }
    if ( lastAnimationTick + animationFramerate > SDL_GetTicks() ) {
        return;
    }
    animationIndex++;
    if (animationIndex >= currentAnimation->frames.size() ) {
        animationIndex = 0;
    }
    setFrame( currentAnimation->frames[ animationIndex ] );
    lastAnimationTick = SDL_GetTicks();
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

void ChompGfxSprite::getAnimationData(uint8_t* bitmap)
{
    currentAnimation = NULL;
    uint8_t* data = ChompBitmap::getAnimationData(bitmap);
    uint8_t animationCount = data[0];
    animationFramerate = 1000 / (uint16_t) data[1];
    uint32_t pos = 2;
    uint8_t animationNameLength;
    uint16_t animationFrames;

    for (uint8_t i = 0; i < animationCount; i++) {
        ChompGfxSpriteAnimationData animation;
        animationNameLength = data[pos];
        char animationName[animationNameLength + 1];
        memcpy(
            animationName,
            &data[pos + 1],
            animationNameLength
        );
        animationName[animationNameLength] = '\0';
        animation.name = std::string(animationName, animationNameLength);
        memcpy(&animationFrames, &data[pos + 1 + animationNameLength], 2);
        animation.frames.clear();
        for (uint16_t j = 0; j < animationFrames; j++) {
            uint16_t animationFrame;
            memcpy(&animationFrame, &data[pos + 3 + animationNameLength + (j * 2)], 2);
            animation.frames.push_back(animationFrame);
        }
        animationData.push_back(animation);
        pos += 3 + animationNameLength + (animationFrames * 2);
    }

}
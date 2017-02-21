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

#include "sprite.h"
char Chomp::GfxSprite::SPRITE_ASSET_PREFIX[] = "spr_";

Chomp::GfxSprite::~GfxSprite()
{
    for (uint16_t i = 0; i < spriteTextures.size(); i++) {
        SDL_DestroyTexture(spriteTextures[i]);
    }
    spriteTextures.clear();
}

bool Chomp::GfxSprite::setFrame(const uint16_t frame)
{
    if (frame >= spriteTextures.size()) {
        return false;
    }
    texture = spriteTextures[frame];
    return true;
}

bool Chomp::GfxSprite::setAnimation(const char* name)
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

void Chomp::GfxSprite::updateAnimationFrame()
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

void Chomp::GfxSprite::setTextures(uint8_t* bitmap)
{
    spriteTextures.clear();
    for (uint16_t i = 0; i < Chomp::Bitmap::getFrameCount(bitmap); i++) {
        spriteTextures.push_back(
            Chomp::Bitmap::getTexture(
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

void Chomp::GfxSprite::getAnimationData(uint8_t* bitmap)
{
    currentAnimation = NULL;
    uint8_t* data = Chomp::Bitmap::getAnimationData(bitmap);
    uint8_t animationCount = data[0];
    animationFramerate = 1000 / (uint16_t) data[1];
    uint32_t pos = 2;
    uint8_t animationNameLength;
    uint16_t animationFrames;

    for (uint8_t i = 0; i < animationCount; i++) {
        Chomp::GfxSpriteAnimationData animation;
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
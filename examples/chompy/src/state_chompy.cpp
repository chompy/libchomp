#include "state_chompy.h"

const char ChompyExampleState::CHOMPY_ASSET[] = "chompy";
const char ChompyExampleState::CHOMPY_ANIM[] = "walk";

void ChompyExampleState::enter()
{
    if (!chompyLayer) {

        uint32_t spriteFileSize = ChompAsset::getAssetSize("spr_chompy");
        if (spriteFileSize > 0) {
            uint8_t spriteData[spriteFileSize];
            ChompGfxSize spriteSize;
            spriteSize.w = 1;
            spriteSize.h = 1;
            ChompAsset::readFile("spr_chompy", 0, &spriteData[0], spriteFileSize);
            chompyLayer = core->window.newLayerFromBitmap(
                &spriteData[0],
                1,
                &spriteSize
            );
        }
    }
    /*if (!chompySprite) {
        chompySprite = new SpriteAnimation(core, (char*) ChompyExampleState::CHOMPY_ASSET);
        chompySprite->setAnimation((char*) ChompyExampleState::CHOMPY_ANIM);
    }*/
}

void ChompyExampleState::exit()
{
    if (chompyLayer) {
        delete chompyLayer;
    }
}

void ChompyExampleState::update()
{
    core->window.addLayerToRenderer(chompyLayer, nullptr, nullptr);
}
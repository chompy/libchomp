#include "state_main.h"

void ChompyStateMain::enter()
{
    map = new ChompyIsometricMap("map1");
    std::cout << map->getSpriteName() << std::endl;
    std::cout << map->getSpriteFrameWidth() << " x " << map->getSpriteFrameHeight() << std::endl;
    std::cout << map->getTileWidth() << " x " << map->getTileHeight() << std::endl;
    std::cout << map->getMapWidth() << " x " << map->getMapHeight() << std::endl;

    uint8_t tileId = map->getTileIdAt(15,15,0);
    std::cout << (int) tileId << std::endl;
    std::cout << (int) map->getTileType(tileId) << std::endl;

}

void ChompyStateMain::exit()
{

}

void ChompyStateMain::update()
{
    map->draw(&core->gfx);
}
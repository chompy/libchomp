#include "state_main.h"

void ChompyStateMain::enter()
{
    map = new ChompyIsometricMap("map1");
    std::cout << map->getSpriteName() << std::endl;
    std::cout << map->getSpriteFrameWidth() << " x " << map->getSpriteFrameHeight() << std::endl;
    std::cout << map->getTileWidth() << " x " << map->getTileHeight() << std::endl;
    std::cout << map->getMapWidth() << " x " << map->getMapHeight() << std::endl;

    std::cout << (int) map->getTileIdAt(15,15,0) << std::endl;

}

void ChompyStateMain::exit()
{

}

void ChompyStateMain::update()
{

}
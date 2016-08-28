#ifndef ISO_MAP_H
#define ISO_MAP_H

#include <string>
#include <vector>
#include "asset/asset.h"

#define TILE_TYPE_NONE 0
#define TILE_TYPE_SOLID 1
#define TILE_TYPE_SLOPE 2
#define TILE_TYPE_HAZARD 3

class ChompyIsometricMap
{
public:

    static char ISO_MAP_ASSET_PREFIX[];

    ChompyIsometricMap(const char* name);
    ~ChompyIsometricMap();

    std::string getSpriteName() { return spriteName; }
    uint16_t getSpriteFrameWidth() { return spriteFrameWidth; }
    uint16_t getSpriteFrameHeight() { return spriteFrameHeight; }
    uint16_t getTileWidth() { return tileWidth; }
    uint16_t getTileHeight() { return tileHeight; }
    uint16_t getMapWidth() { return mapWidth; }
    uint16_t getMapHeight() { return mapHeight; }

    uint8_t getTileIdAt(uint16_t x, uint16_t y, uint16_t z);
    uint8_t getTileType(uint8_t id);

protected:

    std::string spriteName;
    uint16_t spriteFrameWidth, spriteFrameHeight, tileWidth, tileHeight, mapWidth, mapHeight;
    std::vector<uint8_t> tiles;

};

#endif
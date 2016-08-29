#include "map.h"

char ChompyIsometricMap::ISO_MAP_ASSET_PREFIX[] = "imap_";

ChompyIsometricMap::ChompyIsometricMap(const char* name)
{
    // default vars
    spriteFrameWidth = 0; 
    spriteFrameHeight = 0;
    tileWidth = 0; 
    tileHeight = 0;
    mapWidth = 0; 
    mapHeight = 0;
    tileSprite = nullptr;

    // build asset name string
    uint8_t assetPrefixLen = strlen(ChompyIsometricMap::ISO_MAP_ASSET_PREFIX);
    char assetName[assetPrefixLen + strlen(name) + 1];
    memcpy(assetName, ChompyIsometricMap::ISO_MAP_ASSET_PREFIX, assetPrefixLen);
    memcpy(&assetName[assetPrefixLen], name, strlen(name));
    assetName[assetPrefixLen + strlen(name)] = '\0';
    // load asset
    if (!ChompAsset::assetExists(assetName)) {
        return;
    }
    // get filesize
    uint32_t fileSize = ChompAsset::getAssetSize(assetName);
    // read data
    uint8_t* mapData = new uint8_t[fileSize];
    ChompAsset::readFile(assetName, 0, mapData, fileSize);

    // get sprite name
    uint8_t spriteNameLength = mapData[0];
    spriteName.resize(spriteNameLength, ' ');
    memcpy(&spriteName[0], &mapData[1], spriteNameLength);

    // get sprite frame size
    memcpy(&spriteFrameWidth, &mapData[1 + spriteNameLength], 2);
    memcpy(&spriteFrameHeight, &mapData[3 + spriteNameLength], 2);

    // get map size
    memcpy(&mapWidth, &mapData[5 + spriteNameLength], 2);
    memcpy(&mapHeight, &mapData[7 + spriteNameLength], 2);    

    // get tile size
    memcpy(&tileWidth, &mapData[9 + spriteNameLength], 2);
    memcpy(&tileHeight, &mapData[11 + spriteNameLength], 2);

    // get layer count
    uint8_t layerCount = mapData[13 + spriteNameLength];

    // number of tiles
    uint32_t layerTileCount = mapWidth * mapHeight;
    uint32_t totalTileCount = layerTileCount * layerCount;

    // iterate tiles
    uint16_t totalTypes = 0;
    tiles.clear();
    for (uint32_t i = 0; i < totalTileCount; i++) {
        //tile.z = i / totalTileCount;
        //tile.y = (i % layerTileCount) / mapWidth;
        //tile.x = (i % layerTileCount) % mapWidth;
        tiles.push_back( mapData[14 + i + spriteNameLength] );
        if (tiles.back() > totalTypes) {
            totalTypes = tiles.back();
        }
    }

    // map tile types
    uint32_t position = 14 + (mapWidth * mapHeight * layerCount) + spriteNameLength;
    types.clear();
    for (uint16_t i = 0; i < totalTypes; i++) {
        types.push_back( (uint8_t) mapData[position + i] );
    }

    delete[] mapData;

}

uint8_t ChompyIsometricMap::getTileIdAt(uint16_t x, uint16_t y, uint16_t z)
{
    uint32_t index = ((mapWidth * mapHeight) * z) + (mapWidth * y) + x;
    if (x > mapWidth || y > mapHeight || tiles.size() <= index) {
        return 0;
    }
    return tiles[index];
}

uint8_t ChompyIsometricMap::getTileType(uint8_t tid)
{
    if (tid == 0 || (uint16_t) (tid - 1) >= types.size()) {
        return TILE_TYPE_NONE;
    }
    return types[tid - 1];
}

void ChompyIsometricMap::draw(ChompGfx* gfx)
{
    if (!tileSprite) {
        ChompGfxSize size;
        size.w = spriteFrameWidth;
        size.h = spriteFrameHeight;
        tileSprite = gfx->newSprite(spriteName.c_str(), &size);
    }
}
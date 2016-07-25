#ifndef CHOMP_ASSET_H
#define CHOMP_ASSET_H

#include <SDL2/SDL.h>

class ChompAsset
{
public:

    static const char ASSET_FILE[];

    // asset read
    static uint8_t readFileByte(char* name, uint32_t position);
    static void readFile(char* name, uint32_t position, void* buffer, uint32_t length);

    // asset details
    static bool assetExists(char* name);
    static uint32_t getAssetSize(char* name);

protected:

    static void getAssetData(char* name, uint32_t* position, uint32_t* size, uint8_t* nameLength);


};

#endif 
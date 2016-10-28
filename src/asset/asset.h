#ifndef CHOMP_ASSET_H
#define CHOMP_ASSET_H

#include <string>
#include "../sdl_includes.h"
#include "../exception/asset_exception.h"

class ChompAsset
{
public:

    static const char ASSET_FILE[];

    // asset read
    static uint8_t readFileByte(const char* name, const uint32_t position);
    static void readFile(const char* name, const uint32_t position, void* buffer, const uint32_t length);

    // asset details
    static bool assetExists(const char* name);
    static uint32_t getAssetSize(const char* name);

protected:

    static void getAssetData(const char* name, uint32_t* position, uint32_t* size, uint8_t* nameLength);


};

#endif 
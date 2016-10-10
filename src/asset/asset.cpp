#include "asset.h"

const char ChompAsset::ASSET_FILE[] = "assets.dat";

uint8_t ChompAsset::readFileByte(const char* name, const uint32_t position)
{
    // get position/size of asset
    uint32_t assetPosition, assetSize;
    uint8_t nameLength;
    ChompAsset::getAssetData(name, &assetPosition, &assetSize, &nameLength);

    // does not exist
    if (assetSize == 0 || nameLength == 0) {
        std::string message = "Asset '" + std::string( name ) + "' does not exist.";
        throw ChompAssetException(message.c_str());
        return 0;
    }

    // open asset file
    SDL_RWops* file = SDL_RWFromFile(ChompAsset::ASSET_FILE, "rb");
    if (!file) {
        std::string message = "Unable to open asset file. (" + std::string( ChompAsset::ASSET_FILE ) + ")";
        throw ChompAssetException(message.c_str());
        return 0;
    }    

    // jump to position
    SDL_RWseek(file, assetPosition + position, RW_SEEK_SET);

    // read byte
    uint8_t output;
    if (SDL_RWread(file, &output, 1, 1) == 0) {
        SDL_RWclose(file);
        return 0;
    }

    SDL_RWclose(file);
    return output;
}

void ChompAsset::readFile(const char* name, const uint32_t position, void* buffer, const uint32_t length)
{

    // get position/size of asset
    uint32_t assetPosition, assetSize;
    uint8_t nameLength;
    ChompAsset::getAssetData(name, &assetPosition, &assetSize, &nameLength);

    // does not exist
    if (assetSize == 0 || nameLength == 0) {
        std::string message = "Asset '" + std::string( name ) + "' does not exist.";
        throw ChompAssetException(message.c_str());
        return;
    }

    // open asset file
    SDL_RWops* file = SDL_RWFromFile(ChompAsset::ASSET_FILE, "rb");
    if (!file) {
        std::string message = "Unable to open asset file. (" + std::string( ChompAsset::ASSET_FILE ) + ")";
        throw ChompAssetException(message.c_str());
        return;
    }    

    // jump to position
    SDL_RWseek(file, assetPosition + position, RW_SEEK_SET);

    // read
    SDL_RWread(file, buffer, length, 1);
    SDL_RWclose(file);
}

bool ChompAsset::assetExists(const char* name)
{
    uint32_t size = 0;
    uint8_t nameLength = 0;    
    ChompAsset::getAssetData(name, NULL, &size, &nameLength);
    return size > 0 && nameLength > 0;
}

uint32_t ChompAsset::getAssetSize(const char* name)
{
    uint32_t size = 0;
    ChompAsset::getAssetData(name, NULL, &size, NULL);
    return size;
}

void ChompAsset::getAssetData(const char* name, uint32_t* position, uint32_t* size, uint8_t* nameLength)
{

    // open asset file
    SDL_RWops* file = SDL_RWFromFile(ChompAsset::ASSET_FILE, "rb");
    if (!file) {
        std::string message = "Unable to open asset file. (" + std::string( ChompAsset::ASSET_FILE ) + ")";
        throw ChompAssetException(message.c_str());
        return;
    }

    // get number of assets
    uint16_t assetCount;
    if (SDL_RWread(file, &assetCount, 2, 1) == 0) {
        SDL_RWclose(file);
        return;
    }

    // iterate index
    for (uint16_t i = 0; i < assetCount; i++) {

        // get asset name length
        uint8_t assetNameLength;
        if (SDL_RWread(file, &assetNameLength, 1, 1) == 0) {
            break;
        }

        // get asset name
        char assetName[assetNameLength + 1];
        if (SDL_RWread(file, &assetName, assetNameLength, 1) == 0) {
            break;
        }
        assetName[assetNameLength] = '\0';

        // next asset
        if (strcmp(name, assetName) != 0) {
            SDL_RWseek(file, 8, RW_SEEK_CUR);
            continue;
        }

        // is asset
        uint32_t _position, _size;
        if (SDL_RWread(file, &_position, 4, 1) == 0) {
            break;
        }
        if (SDL_RWread(file, &_size, 4, 1) == 0) {
            break;
        }

        // write asset data values
        if (position) {
            *position = _position;
        }
        if (size) {
            *size = _size;
        }
        if (nameLength) {
            *nameLength = assetNameLength;
        }

        SDL_RWclose(file);
        return;

    }

    if (position) {
        *position = 0;
    }
    if (size) {
        *size = 0;
    }
    if (nameLength) {
        *nameLength = 0;
    }

    SDL_RWclose(file);
    return;

}
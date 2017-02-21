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

#include "asset.h"

const char Chomp::Asset::DEFAULT_ASSET_FILE[] = "assets.dat";

Chomp::Asset::Asset()
{
    assetFilename = std::string(Chomp::Asset::DEFAULT_ASSET_FILE);
}

Chomp::Asset::Asset(const char* _assetFilename)
{
    assetFilename = std::string(_assetFilename);
}

Chomp::Asset::~Asset()
{
    
}

uint8_t Chomp::Asset::readFileByte(const char* name, const uint32_t position)
{
    // get position/size of asset
    uint32_t assetPosition, assetSize;
    uint8_t nameLength;
    getAssetData(name, &assetPosition, &assetSize, &nameLength);

    // does not exist
    if (assetSize == 0 || nameLength == 0) {
        std::string message = "Asset '" + std::string( name ) + "' does not exist.";
        throw Chomp::AssetException(message.c_str());
        return 0;
    }

    // open asset file
    SDL_RWops* file = SDL_RWFromFile(assetFilename.c_str(), "rb");
    if (!file) {
        std::string message = "Unable to open asset file. (" + assetFilename + ")";
        throw Chomp::AssetException(message.c_str());
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

void Chomp::Asset::readFile(const char* name, const uint32_t position, void* buffer, const uint32_t length)
{

    // get position/size of asset
    uint32_t assetPosition, assetSize;
    uint8_t nameLength;
    getAssetData(name, &assetPosition, &assetSize, &nameLength);

    // does not exist
    if (assetSize == 0 || nameLength == 0) {
        std::string message = "Asset '" + std::string( name ) + "' does not exist.";
        throw Chomp::AssetException(message.c_str());
        return;
    }

    // open asset file
    SDL_RWops* file = SDL_RWFromFile(assetFilename.c_str(), "rb");
    if (!file) {
        std::string message = "Unable to open asset file. (" + assetFilename + ")";
        throw Chomp::AssetException(message.c_str());
        return;
    }    

    // jump to position
    SDL_RWseek(file, assetPosition + position, RW_SEEK_SET);

    // read
    SDL_RWread(file, buffer, length, 1);
    SDL_RWclose(file);
}

bool Chomp::Asset::assetExists(const char* name)
{
    uint32_t size = 0;
    uint8_t nameLength = 0;    
    getAssetData(name, NULL, &size, &nameLength);
    return size > 0 && nameLength > 0;
}

uint32_t Chomp::Asset::getAssetSize(const char* name)
{
    uint32_t size = 0;
    getAssetData(name, NULL, &size, NULL);
    return size;
}

void Chomp::Asset::getAssetData(const char* name, uint32_t* position, uint32_t* size, uint8_t* nameLength)
{

    // open asset file
    SDL_RWops* file = SDL_RWFromFile(assetFilename.c_str(), "rb");
    if (!file) {
        std::string message = "Unable to open asset file. (" + assetFilename + ")";
        throw Chomp::AssetException(message.c_str());
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
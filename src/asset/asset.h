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

#ifndef CHOMP_ASSET_H
#define CHOMP_ASSET_H

#include <string>
#include "../sdl_includes.h"
#include "../exception/asset_exception.h"

namespace Chomp
{

    /**
     * Reads data from asset file.
     */
    class Asset
    {
    public:

        /**
         * Path to application data directory.
         * @see https://wiki.libsdl.org/SDL_GetBasePath
         */
        static char* ASSET_BASE_PATH;

        /**
         * Name of default file with asset data.
         */
        static const char DEFAULT_ASSET_FILE[];

        /**
         * Constructor.
         */
        Asset();
        Asset(const char* _assetFilename);

        /**
         * Destructor.
         */
        ~Asset();

        /**
         * Reads a single byte from a file stored in
         * the asset file.
         * @param name Subfile name
         * @param position Byte position to read from beginning of subfile
         * @return Byte at given position
         */
        uint8_t readFileByte(const char* name, const uint32_t position);

        /**
         * Load a section of a file stored in the
         * asset file in to a buffer.
         * @param name Subfile name
         * @param position Byte position to start from
         * @param buffer Buffer to write to
         * @param length Number of bytes to read
         */
        void readFile(const char* name, const uint32_t position, void* buffer, const uint32_t length);

        /**
         * Check if given file exists in the asset
         * file.
         * @param name Subfile name
         * @return True if file exists 
         */
        bool assetExists(const char* name);
        
        /**
         * Get size of given file in the asset file.
         * @param name Subfile name
         * @return Size in bytes
         */
        uint32_t getAssetSize(const char* name);

    protected:

        /**
         * Path to asset data file.
         */
        std::string assetFilename;

        /**
         * Retreive details about a given file stored
         * in the asset file.
         * @param name Subfile name.
         * @param position Filled with the byte position of the given file
         * @param size Filled with the size of the given file
         * @param nameLength Filled with the string length of the filename
         */
        void getAssetData(const char* name, uint32_t* position, uint32_t* size, uint8_t* nameLength);

    };
};

#endif 
#ifndef CHOMP_ASSET_H
#define CHOMP_ASSET_H

#include <string>
#include "../sdl_includes.h"
#include "../exception/asset_exception.h"

/**
 * Reads data from asset file.
 */
class ChompAsset
{
public:

    /**
     * Name of file with asset data.
     */
    static const char ASSET_FILE[];

    /**
     * Reads a single byte from a file stored in
     * the asset file.
     * @param name Subfile name
     * @param position Byte position to read from beginning of subfile
     * @return Byte at given position
     */
    static uint8_t readFileByte(const char* name, const uint32_t position);

    /**
     * Load a section of a file stored in the
     * asset file in to a buffer.
     * @param name Subfile name
     * @param position Byte position to start from
     * @param buffer Buffer to write to
     * @param length Number of bytes to read
     */
    static void readFile(const char* name, const uint32_t position, void* buffer, const uint32_t length);

    /**
     * Check if given file exists in the asset
     * file.
     * @param name Subfile name
     * @return True if file exists 
     */
    static bool assetExists(const char* name);
    
    /**
     * Get size of given file in the asset file.
     * @param name Subfile name
     * @return Size in bytes
     */
    static uint32_t getAssetSize(const char* name);

protected:

    /**
     * Retreive details about a given file stored
     * in the asset file.
     * @param name Subfile name.
     * @param position Filled with the byte position of the given file
     * @param size Filled with the size of the given file
     * @param nameLength Filled with the string length of the filename
     */
    static void getAssetData(const char* name, uint32_t* position, uint32_t* size, uint8_t* nameLength);


};

#endif 
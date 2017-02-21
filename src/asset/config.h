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

#ifndef CHOMP_ASSET_CONFIG_H
#define CHOMP_ASSET_CONFIG_H

#include <vector>
#include <string>
#include "../sdl_includes.h"
#include "asset.h"

#define CONFIG_TYPE_STRING 0
#define CONFIG_TYPE_INT 1
#define CONFIG_TYPE_FLOAT 2

namespace Chomp
{

    /**
     * Struct for storing config
     * key/value pairs.
     */
    struct ConfigValue
    {
        std::string key; /**< Key string >*/
        uint8_t type; /**< Type of value >*/
        std::vector<uint8_t> data; /**< Raw value data >*/
    };

    /**
     * Read configuration key/value pairs from config
     * asset file.
     */
    class Config
    {
    public:

        /**
         * Config asset name prefix
         */
        static char CONFIG_ASSET_PREFIX[];

        /**
         * Constructor.
         * Load config data with its filename.
         * @param configName Config filename.
         */
        Config(const char* configName);

        /**
         * Constructor.
         * Load config data from a byte array.
         * @param data Byte array
         * @param size Size of byte array
         */
        Config(uint8_t* data, uint32_t size);

        /**
         * Destructor.
         */
        ~Config();

        /**
         * Check if given key exists.
         * @param key Key to check
         * @return True if key exists
         */
        bool hasKey(std::string key);

        /**
         * Retrieve string value from config.
         * @param key Key containing string value
         * @return String value
         */
        std::string getString(std::string key);

        /**
         * Retrieve string value from config.
         * @param key Key containing string value
         * @param defaultValue Value to return if key does not exist
         * @return String value
         */    
        std::string getString(std::string key, std::string defaultValue);

        /**
         * Retrieve integer value from config.
         * @param key Key containing integer value
         * @return Integer value
         */
        int32_t getInt(std::string key);

        /**
         * Retrieve integer value from config.
         * @param key Key containing integer value
         * @param defaultValue Value to return if key does not exist
         * @return Integer value
         */
        int32_t getInt(std::string key, int32_t defaultValue);

        /**
         * Retrieve float value from config.
         * @param key Key containing float value
         * @return Integer value
         */
        float getFloat(std::string key);

        /**
         * Retrieve float value from config.
         * @param key Key containing float value
         * @param defaultValue Value to return if key does not exist
         * @return Integer value
         */
        float getFloat(std::string key, float defaultValue);

    protected:

        /**
         * Load config data from byte array.
         * @param data Byte array
         * @param size Size of byte array
         */
        void loadConfig(uint8_t* data, uint32_t size);

        /**
         * Vector containing key/value pairs.
         */
        std::vector<ConfigValue> values;

    };
};

#endif 
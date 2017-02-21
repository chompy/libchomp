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

#include "config.h"

char Chomp::Config::CONFIG_ASSET_PREFIX[] = "conf_";

Chomp::Config::Config(const char* configName)
{
    // build asset name string
    uint8_t assetPrefixLen = strlen(Chomp::Config::CONFIG_ASSET_PREFIX);
    char assetName[assetPrefixLen + strlen(configName) + 1];
    memcpy(assetName, Chomp::Config::CONFIG_ASSET_PREFIX, assetPrefixLen);
    memcpy(&assetName[assetPrefixLen], configName, strlen(configName));
    assetName[assetPrefixLen + strlen(configName)] = '\0';
    Chomp::Asset asset;
    // get filesize
    uint32_t fileSize = asset.getAssetSize(assetName);
    // get data
    std::vector<uint8_t> configData(fileSize, 0);
    asset.readFile(assetName, 0, &configData[0], fileSize);
    loadConfig(&configData[0], fileSize);
}

Chomp::Config::Config(uint8_t* data, uint32_t size)
{
    loadConfig(data, size);
}

Chomp::Config::~Config()
{
    values.clear();
}

void Chomp::Config::loadConfig(uint8_t* data, uint32_t size)
{
    values.clear();
    uint32_t position = 0;
    while (position < size) {
        Chomp::ConfigValue configValue;
        uint16_t keyLength = 0;
        memcpy(&keyLength, &data[position], 2);
        configValue.key.resize(keyLength, ' ');
        memcpy(&configValue.key[0], &data[position + 2], keyLength);
        position += 2 + keyLength;
        configValue.type = data[position];
        position += 1;
        switch (configValue.type) {
            case CONFIG_TYPE_STRING:
            {
                uint16_t strLength = 0;
                memcpy(&strLength, &data[position], 2);
                configValue.data.resize(strLength, 0);
                memcpy(&configValue.data[0], &data[position + 2], strLength);
                position += 2 + strLength;
                break;
            }
            case CONFIG_TYPE_INT:
            {
                configValue.data.resize(4, 0);
                memcpy(&configValue.data[0], &data[position], 4);
                position += 4;
                break;
            }
            case CONFIG_TYPE_FLOAT:
            {   
                configValue.data.resize(4, 0);
                memcpy(&configValue.data[0], &data[position], 4);
                position += 4;
                break;
            }
        }
        values.push_back(configValue);
    }
}

bool Chomp::Config::hasKey(std::string key)
{
    for (uint32_t i = 0; i < values.size(); i++) {
        if (values[i].key.compare(key) == 0) {
            return true;
        }
    }
    return false;
}

std::string Chomp::Config::getString(std::string key)
{
    return getString(key, "");
}

std::string Chomp::Config::getString(std::string key, std::string defaultValue)
{
    for (uint32_t i = 0; i < values.size(); i++) {
        if (values[i].key.compare(key) == 0) {
            if (values[i].type != CONFIG_TYPE_STRING) {
                break;
            }
            return std::string((const char*) &values[i].data[0], values[i].data.size());
        }
    }
    return defaultValue;
}

int32_t Chomp::Config::getInt(std::string key)
{
    return getInt(key, 0);
}

int32_t Chomp::Config::getInt(std::string key, int32_t defaultValue)
{
    for (uint32_t i = 0; i < values.size(); i++) {
        if (values[i].key.compare(key) == 0) {
            if (values[i].type != CONFIG_TYPE_INT) {
                break;
            }
            int32_t value = 0;
            memcpy(&value, &values[i].data[0], 4);
            return value;
        }
    }
    return defaultValue;
}

float Chomp::Config::getFloat(std::string key)
{
    return getFloat(key, 0);
}

float Chomp::Config::getFloat(std::string key, float defaultValue)
{
    for (uint32_t i = 0; i < values.size(); i++) {
        if (values[i].key.compare(key) == 0) {
            if (values[i].type != CONFIG_TYPE_FLOAT) {
                break;
            }
            float value = 0;
            memcpy(&value, &values[i].data[0], 4);
            return value;
        }
    }
    return defaultValue;
}
#ifndef CHOMP_ASSET_CONFIG_H
#define CHOMP_ASSET_CONFIG_H

#include <vector>
#include <string>
#include "../sdl_includes.h"
#include "asset.h"

#define CONFIG_TYPE_STRING 0
#define CONFIG_TYPE_INT 1
#define CONFIG_TYPE_FLOAT 2

struct ChompConfigValue
{
    std::string key;
    uint8_t type;
    std::vector<uint8_t> data;
};

class ChompConfig
{
public:

    static char CONFIG_ASSET_PREFIX[];

    ChompConfig(const char* configName);
    ChompConfig(uint8_t* data, uint32_t size);
    ~ChompConfig();

    bool hasKey(std::string key);
    std::string getString(std::string key);
    int32_t getInt(std::string key);
    float getFloat(std::string key);

protected:

    void loadConfig(uint8_t* data, uint32_t size);

    std::vector<ChompConfigValue> values;


};

#endif 
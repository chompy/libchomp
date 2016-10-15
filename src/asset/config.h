#ifndef CHOMP_ASSET_CONFIG_H
#define CHOMP_ASSET_CONFIG_H

#ifndef ANDROID
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
#include <vector>
#include <string>

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

    ChompConfig(uint8_t* data, uint32_t size);
    ~ChompConfig();

    bool hasKey(std::string key);
    std::string getString(std::string key);
    int32_t getInt(std::string key);
    float getFloat(std::string key);

protected:

std::vector<ChompConfigValue> values;


};

#endif 
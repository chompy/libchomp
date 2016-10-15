#include "config.h"

ChompConfig::ChompConfig(uint8_t* data, uint32_t size)
{
    values.clear();
    uint32_t position = 0;

    uint8_t type = 0;


    while (position < size) {

        ChompConfigValue configValue;
        configValue.type = data[position];
        position += 1;

        switch (type) {
            case CONFIG_TYPE_STRING:
            {
                uint16_t strLength = 0;
                memcpy(&strLength, &data[position], 2);
                configValue.data.resize(strLength, 0);
                memcpy(&configValue.data[0], &data[position + 2], strLength);
                break;
            }
            case CONFIG_TYPE_INT:
            {
                configValue.data.resize(4, 0);
                memcpy(&configValue.data[0], &data[position], 4);
                break;
            }
            case CONFIG_TYPE_FLOAT:
            configValue.data.resize(4, 0);
            {   memcpy(&configValue.data[0], &data[position], 4);
                break;
            }
        }
        
    }
}

bool ChompConfig::hasKey(std::string key)
{
    for (uint32_t i = 0; i < values.size(); i++) {
        if (values[i].key == key) {
            return true;
        }
    }
    return false;
}

std::string ChompConfig::getString(std::string key)
{
    for (uint32_t i = 0; i < values.size(); i++) {
        if (values[i].key == key) {
            if (values[i].type != CONFIG_TYPE_STRING) {
                break;
            }
            return std::string(&values[i].data[0], values[i].data.size());
        }
    }
    return std::string;
}

int32_t ChompConfig::getInt(std::string key)
{
    for (uint32_t i = 0; i < values.size(); i++) {
        if (values[i].key == key) {
            if (values[i].type != CONFIG_TYPE_INT) {
                break;
            }
            int32_t value = 0;
            memcpy(&value[0], &values[i].data[0], 4);
            return value;
        }
    }
    return 0;
}

float ChompConfig::getFloat(std::string key)
{
    for (uint32_t i = 0; i < values.size(); i++) {
        if (values[i].key == key) {
            if (values[i].type != CONFIG_TYPE_FLOAT) {
                break;
            }
            float value = 0;
            memcpy(&value[0], &values[i].data[0], 4);
            return value;
        }
    }
    return 0;
}
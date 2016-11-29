#include "stdint.h"
#include <stdlib.h>
#include <iostream>
#include "src/chomp.h"

int main(int argc, char **argv) {
    ChompConfig config("sample_config");
    std::cout << "key1: " << config.getString("key1") << std::endl;
    std::cout << "key2.test1: " << config.getString("key2.test1") << std::endl;
    std::cout << "key2.test2: " << config.getInt("key2.test2") << std::endl;
    std::cout << "key2.test3: " << config.getFloat("key2.test3") << std::endl;
    std::cout << "key2.test4.0: " << config.getInt("key2.test4.0") << std::endl;
    std::cout << "key2.test4.1: " << config.getInt("key2.test4.1") << std::endl;
    return 1;
}
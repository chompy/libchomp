#include "stdint.h"
#include <stdlib.h>
#include <iostream>

#include "src/chomp.h"
#include "state_chompy.h"

int main(int argc, char **argv) {
    Chomp chomp;
    ChompyExampleState chompyState(&chomp.core);
    chomp.start(&chompyState);
    return 1;
}
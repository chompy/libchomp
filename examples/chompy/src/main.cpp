#include "stdint.h"
#include <stdlib.h>
#include <iostream>

#include "chomp.h"
#include "state_chompy.h"

int main(int argc, char **argv) {
    Chomp::Entry chomp;
    ChompyExampleState chompyState(&chomp.core);   
    chomp.start(&chompyState);
    return 1;
}
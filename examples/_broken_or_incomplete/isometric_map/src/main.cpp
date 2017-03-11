#include "stdint.h"
#include <stdlib.h>
#include <iostream>

#include "chomp.h"
#include "state_main.h"

int main(int argc, char **argv) {
    Chomp chomp;
    ChompyStateMain mainState(&chomp.core);
    chomp.start(&mainState);
    return 1;
}
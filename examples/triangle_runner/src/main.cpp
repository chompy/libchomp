#include "stdint.h"
#include <stdlib.h>
#include <iostream>

#include "src/chomp.h"
#include "state_main.h"
#include "state_play.h"

int main(int argc, char **argv) {
    Chomp chomp;
    ChompyStatePlay playState(&chomp.core);
    ChompyStateMain mainState(&chomp.core, &playState);
    chomp.core.gfx.setWindowTitle("Triangle Runner -- LibChomp Example");
    chomp.start(&mainState);
    return 1;
}
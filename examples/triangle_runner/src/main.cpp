#include "stdint.h"
#include <stdlib.h>
#include <iostream>

#include "chomp.h"
#include "state_main.h"
#include "state_play.h"

int main(int argc, char **argv) {
    Chomp chomp;
    ChompyStatePlay playState(&chomp.core);
    chomp.core.gfx.setWindowTitle("Triangle Runner -- LibChomp Example");
    chomp.start(&playState);
    return 1;
}
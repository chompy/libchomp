#include "state_main.h"

const char ChompyStateMain::SAMPLE_ASSET[] = "chord";
const char ChompyStateMain::SAMPLE_MUSIC[] = "organfinale";


void ChompyStateMain::enter()
{
    core->sfx.music.loadMusic(ChompyStateMain::SAMPLE_MUSIC, MUSIC_PLAY, 1);
    if (!sample) {
        sample = core->sfx.loadSample(ChompyStateMain::SAMPLE_ASSET);
    }
}

void ChompyStateMain::exit()
{
}

void ChompyStateMain::update()
{
    if (sample && sample->getStatus() == SFX_STOP && core->input.mouse.pressed(MOUSE_BUTTON_LEFT)) {
        sample->play();
    }
}
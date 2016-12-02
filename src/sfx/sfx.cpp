#include "sfx.h"

char ChompSfx::MUSIC_ASSET_PREFIX[] = "mus_";

ChompSfx::ChompSfx()
{
    #ifndef WITHOUT_SDL_MIXER
    int flags = MIX_INIT_OGG;
    int initted = Mix_Init(MIX_INIT_OGG);
    if ((initted&flags) != flags) {
        std::string exceptionMsg = Mix_GetError();
        if (exceptionMsg.empty()) {
            exceptionMsg = "Failed to init SDL Mixer.";
        }
        throw ChompSdlMixerException(exceptionMsg);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
        throw ChompSdlMixerException(Mix_GetError());   
    }
    Mix_AllocateChannels(SFX_CHANNELS);
    #endif
}

ChompSfx::~ChompSfx()
{
    #ifndef WITHOUT_SDL_MIXER
    Mix_Quit();
    #endif
}
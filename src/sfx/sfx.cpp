#include "sfx.h"

ChompSfx::ChompSfx()
{
    samples.clear();
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
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096)==-1) {
        throw ChompSdlMixerException(Mix_GetError());   
    }
    Mix_AllocateChannels(SFX_CHANNELS);
    #endif
}

ChompSfx::~ChompSfx()
{
    unloadAllSamples();
    #ifndef WITHOUT_SDL_MIXER
    music.unloadMusic();
    Mix_Quit();
    #endif
}

ChompSfxSample* ChompSfx::loadSample(const char* name)
{
    samples.push_back( ChompSfxSample(name) );
    return &samples[samples.size() - 1];
}

void ChompSfx::unloadAllSamples()
{
    #ifndef WITHOUT_SDL_MIXER
    Mix_HaltChannel(-1);
    #endif
    samples.clear();
}
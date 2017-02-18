#include "sfx.h"

Chomp::Sfx::Sfx()
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
        throw Chomp::SdlMixerException(exceptionMsg);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096)==-1) {
        throw Chomp::SdlMixerException(Mix_GetError());   
    }
    Mix_AllocateChannels(CHOMP_SFX_CHANNELS);
    #endif
}

Chomp::Sfx::~Sfx()
{
    unloadAllSamples();
    #ifndef WITHOUT_SDL_MIXER
    music.unloadMusic();
    Mix_Quit();
    #endif
}

Chomp::SfxSample* Chomp::Sfx::loadSample(const char* name)
{
    samples.push_back( Chomp::SfxSample(name) );
    return &samples[samples.size() - 1];
}

void Chomp::Sfx::unloadAllSamples()
{
    #ifndef WITHOUT_SDL_MIXER
    Mix_HaltChannel(-1);
    #endif
    samples.clear();
}
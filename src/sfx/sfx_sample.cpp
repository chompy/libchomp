#include "sfx_sample.h"

char Chomp::SfxSample::SAMPLE_ASSET_PREFIX[] = "sfx_";

Chomp::SfxSample::SfxSample(const char* name)
{
    channel = -1;

    #ifndef WITHOUT_SDL_MIXER
    // build asset name string
    std::string assetName = std::string(Chomp::SfxSample::SAMPLE_ASSET_PREFIX) + std::string(name);
    // init asset handler
    Chomp::Asset asset;
    // load asset
    if (!asset.assetExists(assetName.c_str())) {
        return;
    }
    // get filesize
    uint32_t fileSize = asset.getAssetSize(assetName.c_str());
    // get data
    sampleData.resize(fileSize);
    asset.readFile(assetName.c_str(), 0, &sampleData[0], fileSize);
    #endif
}

Chomp::SfxSample::~SfxSample()
{
    freeChunk();
    sampleData.clear();
}

void Chomp::SfxSample::freeChunk()
{
    #ifndef WITHOUT_SDL_MIXER
    if (channel >= 0) {
        Mix_HaltChannel(channel);
        Mix_Chunk* chunk = Mix_GetChunk(channel);
        if (chunk) {
            Mix_FreeChunk(chunk);
        }
    }
    #endif
}

uint8_t Chomp::SfxSample::getStatus()
{
    if (sampleData.size() == 0) {
        return CHOMP_SFX_FAILED;
    }
    if (channel < 0 || !Mix_Playing(channel)) {
        return CHOMP_SFX_STOP;
    }
    switch(Mix_FadingChannel(channel))
    {
        case MIX_FADING_IN:
        {
            return CHOMP_SFX_FADEIN;
            break;
        }
        case MIX_FADING_OUT:
        {
            return CHOMP_SFX_FADEOUT;
            break;
        }
    }
    return CHOMP_SFX_PLAY;
}

void Chomp::SfxSample::setMode(uint8_t operation)
{
    setMode(operation, 1, CHOMP_SFX_DEFAULT_FADE, CHOMP_SFX_DEFAULT_TICKS);
}

void Chomp::SfxSample::setMode(uint8_t operation, int16_t loops)
{
    setMode(operation, loops, CHOMP_SFX_DEFAULT_FADE, CHOMP_SFX_DEFAULT_TICKS);
}

void Chomp::SfxSample::setMode(uint8_t operation, int16_t loops, int32_t fadeDuration)
{
    setMode(operation, loops, fadeDuration, CHOMP_SFX_DEFAULT_TICKS);
}

void Chomp::SfxSample::setMode(uint8_t operation, int16_t loops, int32_t fadeDuration, int32_t ticks)
{
    #ifndef WITHOUT_SDL_MIXER
    // make sure asset is available
    if (sampleData.size() == 0) {
        return;
    }

    switch (operation)
    {

        case CHOMP_SFX_PLAY:
        {
            freeChunk();
            if (loops == 0) {
                return;
            }
            SDL_RWops* sampleDataRW = SDL_RWFromMem(&sampleData[0], sampleData.size());
            Mix_Chunk* chunk = Mix_LoadWAV_RW(sampleDataRW, 1);
            channel = Mix_PlayChannelTimed(
                channel,
                chunk,
                loops - 1, // loops+1 times, which is different from Mix_PlayMusic, normalize by subtracting 1
                ticks
            );
            break;
        }

        case CHOMP_SFX_STOP:
        {
            if (channel < 0) {
                break;
            }
            freeChunk();
            break;
        }

        case CHOMP_SFX_FADEIN:
        {
            freeChunk();
            if (loops == 0) {
                return;
            }
            SDL_RWops* sampleDataRW = SDL_RWFromMem(&sampleData[0], sampleData.size());
            Mix_Chunk* chunk = Mix_LoadWAV_RW(sampleDataRW, 1);
            channel = Mix_FadeInChannelTimed(
                channel,
                chunk,
                loops - 1, // loops+1 times, which is different from Mix_PlayMusic, normalize by subtracting 1
                fadeDuration,
                ticks
            );
            break;
        }

        case CHOMP_SFX_FADEOUT:
        {
            if (channel < 0) {
                break;
            }
            Mix_FadeOutChannel(
                channel,
                fadeDuration
            );
            break;
        }

    }
    #endif
}

void Chomp::SfxSample::setVolume(uint8_t volume)
{
    if (channel < 0) {
        return;
    }
    Mix_Volume(
        channel,
        volume * (MIX_MAX_VOLUME / 100)
    );
}

uint8_t Chomp::SfxSample::getVolume()
{
    if (!channel) {
        return 0;
    }
    return Mix_Volume(channel, -1) * (100 / MIX_MAX_VOLUME);
}
#include "sfx_sample.h"

char ChompSfxSample::SAMPLE_ASSET_PREFIX[] = "sfx_";

ChompSfxSample::ChompSfxSample(char* name)
{
    channel = -1;
    chunk = NULL;

    #ifndef WITHOUT_SDL_MIXER
    // build asset name string
    uint8_t assetPrefixLen = strlen(ChompSfxSample::SAMPLE_ASSET_PREFIX);
    char assetName[assetPrefixLen + strlen(name) + 1];
    memcpy(assetName, ChompSfxSample::SAMPLE_ASSET_PREFIX, assetPrefixLen);
    memcpy(&assetName[assetPrefixLen], name, strlen(name));
    assetName[assetPrefixLen + strlen(name)] = '\0';
    // load asset
    if (!ChompAsset::assetExists(assetName)) {
        status = SFX_LOAD_FAILED;
        return;
    }

    // get filesize
    uint32_t fileSize = ChompAsset::getAssetSize(assetName);

    // get data
    sampleData.resize(fileSize);
    ChompAsset::readFile(assetName, 0, &sampleData[0], fileSize);
    SDL_RWops* sampleDataRW = SDL_RWFromMem(&sampleData[0], fileSize);
    chunk = Mix_LoadWAV_RW(sampleDataRW, 1);
    #endif
}

ChompSfxSample::~ChompSfxSample()
{
    #ifndef WITHOUT_SDL_MIXER
    if (chunk) {
        Mix_FreeChunk(chunk)
    }
    #endif
    sampleData.clear();
}

uint8_t ChompSfxSample::getStatus()
{
    if (!chunk) {
        return SFX_FAILED;
    }
    if (channel < 0 || !Mix_Playing(channel)) {
        return SFX_STOP;
    }
    switch(Mix_FadingChannel(channel))
    {
        case MIX_FADING_IN:
        {
            return SFX_FADEIN;
            break;
        }
        case MIX_FADING_OUT:
        {
            return SFX_FADEOUT;
            break;
        }
    }
    return SFX_PLAY;
}

void ChompSfxSample::setSample(uint8_t operation)
{
    setSample(operation, 0, SFX_DEFAULT_FADEIN, SFX_DEFAULT_TICKS);
}

void ChompSfxSample::setSample(uint8_t operation, int16_t loops)
{
    setSample(operation, loops, SFX_DEFAULT_FADE, SFX_DEFAULT_TICKS);
}

void ChompSfxSample::setSample(uint8_t operation, int16_t loops, int32_t fadeDuration)
{
    setSample(operation, loops, fadeDuration, SFX_DEFAULT_TICKS);
}

void ChompSfxSample::setSample(uint8_t operation, int16_t loops, int32_t fadeDuration, int32_t ticks)
{
    // make sure chunk is available
    if (!chunk) {
        return;
    }

    switch (operation)
    {

        case SFX_PLAY:
        {
            if (loops == 0) {
                return;
            }
            if (channel >= 0) {
                Mix_HaltChannel(channel);
                channel = -1;
            }
            channel = Mix_PlayChannelTimed(
                -1
                chunk,
                loops - 1, // loops+1 times, which is different from Mix_PlayMusic, normalize by subtracting 1
                ticks
            )
            break;
        }

        case SFX_STOP:
        {
            if (channel < 0) {
                break;
            }
            Mix_HaltChannel(channel);
            channel = -1;
            break;
        }

        case SFX_FADEIN:
        {
            if (loops == 0) {
                return;
            }
            if (channel >= 0) {
                Mix_HaltChannel(channel);
                channel = -1;
            }
            channel = Mix_FadeInChannelTimed(
                -1,
                chunk,
                loops - 1,
                fadeDuration,
                ticks
            );
            break;
        }

        case SFX_FADEOUT:
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

}

void ChompSfxSample::setSampleVolume(uint8_t volume)
{
    if (!chunk) {
        return;
    }
    Mix_VolumeChunk(
        chunk,
        volume * (MIX_MAX_VOLUME / 100)
    );
}

uint8_t ChompSfxSample::getSampleVolume()
{
    if (!chunk) {
        return 0;
    }
    return Mix_VolumeChunk(chunk, -1) * (100 / MIX_MAX_VOLUME);
}
#include "sfx_sample.h"

char ChompSfxSample::SAMPLE_ASSET_PREFIX[] = "sfx_";

ChompSfxSample::ChompSfxSample(char* name)
{
    channel = -100;
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
    if (!chunk) {
        status = SFX_LOAD_FAILED;
        return;
    }
    status = SFX_READY;
    #else
    status = SFX_NO_SDL_MIXER;
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


void ChompSfxSample::setSample(uint8_t operation, int16_t loops, int32_t fadeDuration)
{
    // make sure not in error status
    if (status >= 200 || !chunk) {
        return;
    }

    switch (operation)
    {

        case SFX_PLAY:
        {
            channel = Mix_PlayChannel(
                -1
                chunk
            )
            break;
        }

    }

}
#include "music.h"

ChompSfxMusic::ChompSfxMusic()
{
    music = NULL;
    musicData.clear();
    queuedMusic = "";
    queuedMusicOperation = 0;
    queuedMusicLoops = 0;
    queuedMusicFadeDuration = 0;
}

ChompSfxMusic::~ChompSfxMusic()
{
    unloadMusic();
}

uint8_t ChompSfxMusic::loadMusic(char* name)
{
    return loadMusic(name, MUSIC_STOP, 0, 0);
}

uint8_t ChompSfxMusic::loadMusic(char* name, uint8_t operation)
{
    return loadMusic(name, operation, -1, 0);
}

uint8_t ChompSfxMusic::loadMusic(char* name, uint8_t operation, int16_t loops)
{
    return loadMusic(name, operation, loops, 0);
}

uint8_t ChompSfxMusic::loadMusic(char* name, uint8_t operation, int16_t loops, int16_t fadeDuration)
{
    #ifndef WITHOUT_SDL_MIXER
    if (!name || operation == MUSIC_FADEOUT) {
        return MUSIC_LOAD_FAILED;
    }

    // queue up music if previous music is fading out
    if (Mix_FadingMusic() == MIX_FADING_OUT) {
        queuedMusic = std::string(name);
        queuedMusicOperation = operation;
        queuedMusicLoops = loops;
        queuedMusicFadeDuration = fadeDuration;
        return MUSIC_LOAD_QUEUED;
    }

    // build asset name string
    uint8_t assetPrefixLen = strlen(ChompSfxMusic::MUSIC_ASSET_PREFIX);
    char assetName[assetPrefixLen + strlen(name) + 1];
    memcpy(assetName, ChompSfxMusic::MUSIC_ASSET_PREFIX, assetPrefixLen);
    memcpy(&assetName[assetPrefixLen], name, strlen(name));
    assetName[assetPrefixLen + strlen(name)] = '\0';
    // load asset
    if (!ChompAsset::assetExists(assetName)) {
        return MUSIC_LOAD_FAILED;
    }

    // get filesize
    uint32_t fileSize = ChompAsset::getAssetSize(assetName);

    // get data
    musicData.resize(fileSize);
    ChompAsset::readFile(assetName, 0, &musicData[0], fileSize);
    SDL_RWops* musicDataRW = SDL_RWFromMem(&musicData[0], fileSize);

    // load music
    unloadMusic();
    music = Mix_LoadMUS_RW(musicDataRW, 1);
    setMusic(operation, loops, fadeDuration);
    return MUSIC_LOAD_COMPLETE;
    #else
    return MUSIC_LOAD_FAILED;
    #endif
}

void ChompSfxMusic::unloadMusic()
{
    #ifndef WITHOUT_SDL_MIXER
    Mix_HaltMusic();
    if (music) {
        Mix_FreeMusic(music);
        music = NULL;
        musicData.clear();
    }
    #endif
}

bool ChompSfxMusic::checkMusicQueue()
{
    #ifndef WITHOUT_SDL_MIXER
    if (!queuedMusic.empty() && Mix_FadingMusic() != MIX_FADING_OUT && !Mix_PlayingMusic()) {
        loadMusic((char*) queuedMusic.c_str(), queuedMusicOperation, queuedMusicLoops, queuedMusicFadeDuration);
        queuedMusic = "";
        queuedMusicOperation = 0;
        queuedMusicLoops = 0;
        queuedMusicFadeDuration = 0;
        return true;
    }
    #endif
    return false;
}

void ChompSfxMusic::setMusic(uint8_t operation)
{
    setMusic(operation, -1, 0);
}

void ChompSfxMusic::setMusic(uint8_t operation, int16_t loops)
{
    setMusic(operation, loops, 0);
}

void ChompSfxMusic::setMusic(uint8_t operation, int16_t loops, int32_t fadeDuration)
{
    #ifndef WITHOUT_SDL_MIXER
    switch (operation) {
        case MUSIC_STOP:
        {
            Mix_HaltMusic();
            break;
        }
        case MUSIC_PLAY:
        {
            if (music) {
                Mix_PlayMusic(music, loops);
            }
            break;
        }
        case MUSIC_FADEIN:
        {
            if (music) {
                Mix_FadeInMusic(music, loops, fadeDuration);
            }
            break;
        }
        case MUSIC_FADEOUT:
        {
            if (Mix_PlayingMusic()) {
                Mix_FadeOutMusic(fadeDuration);
            }
            break;
        }
    }
    #endif
}
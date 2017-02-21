/**
    This file is part of Libchomp.

    Libchomp is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Libchomp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Libchomp.  If not, see <http://www.gnu.org/licenses/>.
**/

#include "music.h"

char Chomp::SfxMusic::MUSIC_ASSET_PREFIX[] = "mus_";

Chomp::SfxMusic::SfxMusic()
{
    music = NULL;
    musicData.clear();
    queuedMusic = "";
    queuedMusicOperation = 0;
    queuedMusicLoops = 0;
    queuedMusicFadeDuration = 0;
}

Chomp::SfxMusic::~SfxMusic()
{
    unloadMusic();
}

uint8_t Chomp::SfxMusic::loadMusic(const char* name)
{
    return loadMusic(name, CHOMP_SFX_MUSIC_STOP, 0, 0);
}

uint8_t Chomp::SfxMusic::loadMusic(const char* name, uint8_t operation)
{
    return loadMusic(name, operation, -1, 0);
}

uint8_t Chomp::SfxMusic::loadMusic(const char* name, uint8_t operation, int16_t loops)
{
    return loadMusic(name, operation, loops, 0);
}

uint8_t Chomp::SfxMusic::loadMusic(const char* name, uint8_t operation, int16_t loops, int16_t fadeDuration)
{
    #ifndef WITHOUT_SDL_MIXER
    if (!name || operation == CHOMP_SFX_MUSIC_FADEOUT) {
        return CHOMP_SFX_MUSIC_LOAD_FAILED;
    }

    // queue up music if previous music is fading out
    if (Mix_FadingMusic() == MIX_FADING_OUT) {
        queuedMusic = std::string(name);
        queuedMusicOperation = operation;
        queuedMusicLoops = loops;
        queuedMusicFadeDuration = fadeDuration;
        return CHOMP_SFX_MUSIC_LOAD_QUEUED;
    }
    // init asset handler
    Chomp::Asset asset;
    // build asset name string
    std::string assetName = std::string(Chomp::SfxMusic::MUSIC_ASSET_PREFIX) + std::string(name);
    // load asset
    if (!asset.assetExists(assetName.c_str())) {
        return CHOMP_SFX_MUSIC_LOAD_FAILED;
    }

    // get filesize
    uint32_t fileSize = asset.getAssetSize(assetName.c_str());

    // get data
    musicData.resize(fileSize);
    asset.readFile(assetName.c_str(), 0, &musicData[0], fileSize);
    SDL_RWops* musicDataRW = SDL_RWFromMem(&musicData[0], fileSize);

    // load music
    unloadMusic();
    music = Mix_LoadMUS_RW(musicDataRW, 1);
    setMusic(operation, loops, fadeDuration);
    return CHOMP_SFX_MUSIC_LOAD_COMPLETE;
    #else
    return CHOMP_SFX_MUSIC_LOAD_FAILED;
    #endif
}

void Chomp::SfxMusic::unloadMusic()
{
    #ifndef WITHOUT_SDL_MIXER
    if (music) {
        Mix_FreeMusic(music);
        music = NULL;
        musicData.clear();
    }
    #endif
}

bool Chomp::SfxMusic::checkMusicQueue()
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

void Chomp::SfxMusic::setMusic(uint8_t operation)
{
    setMusic(operation, CHOMP_SFX_MUSIC_DEFAULT_LOOPS, CHOMP_SFX_MUSIC_DEFAULT_FADE);
}

void Chomp::SfxMusic::setMusic(uint8_t operation, int16_t loops)
{
    setMusic(operation, loops, CHOMP_SFX_MUSIC_DEFAULT_FADE);
}

void Chomp::SfxMusic::setMusic(uint8_t operation, int16_t loops, int32_t fadeDuration)
{
    #ifndef WITHOUT_SDL_MIXER
    switch (operation) {
        case CHOMP_SFX_MUSIC_STOP:
        {
            Mix_HaltMusic();
            break;
        }
        case CHOMP_SFX_MUSIC_PLAY:
        {
            if (music) {
                Mix_PlayMusic(music, loops);
            }
            break;
        }
        case CHOMP_SFX_MUSIC_FADEIN:
        {
            if (music) {
                Mix_FadeInMusic(music, loops, fadeDuration);
            }
            break;
        }
        case CHOMP_SFX_MUSIC_FADEOUT:
        {
            if (Mix_PlayingMusic()) {
                Mix_FadeOutMusic(fadeDuration);
            }
            break;
        }
    }
    #endif
}

void Chomp::SfxMusic::setVolume(uint8_t volume)
{
    Mix_VolumeMusic(
        volume * (MIX_MAX_VOLUME / 100)
    );
}

uint8_t Chomp::SfxMusic::getVolume()
{
    return Mix_VolumeMusic(-1) * (100 / MIX_MAX_VOLUME);
}
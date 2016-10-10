#ifndef CHOMP_SFX_H
#define CHOMP_SFX_H

#include <string>
#include <vector>

#ifndef ANDROID
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#ifndef WITHOUT_SDL_MIXER
#ifndef ANDROID
#include <SDL2/SDL_mixer.h>
#else
#include <SDL_mixer.h>
#endif
#include "../exception/sdl_mixer_exception.h"
#endif

#include "../asset/asset.h"

#include <iostream>

#define MUSIC_STOP 0
#define MUSIC_PLAY 1
#define MUSIC_FADEIN 2
#define MUSIC_FADEOUT 3

#define MUSIC_LOAD_FAILED 0
#define MUSIC_LOAD_COMPLETE 1
#define MUSIC_LOAD_QUEUED 2

class ChompSfx {

public:

    static char MUSIC_ASSET_PREFIX[];

    ChompSfx();
    ~ChompSfx();

    // music (one at a time)
    uint8_t loadMusic(char* name);
    uint8_t loadMusic(char* name, uint8_t operation);
    uint8_t loadMusic(char* name, uint8_t operation, int16_t loops);
    uint8_t loadMusic(char* name, uint8_t operation, int16_t loops, int16_t fadeDuration);
    void unloadMusic();
    void checkMusicQueue();
    void setMusic(uint8_t operation);
    void setMusic(uint8_t operation, int16_t loops);
    void setMusic(uint8_t operation, int16_t loops, int16_t fadeDuration);
    
    // sfx
    void loadChunk(char* name);

    #ifndef WITHOUT_SDL_MIXER
    Mix_Music* music;
    #else
    void* music;
    #endif

protected:

    std::vector<uint8_t> musicData;
    
    std::string queuedMusic;
    uint8_t queuedMusicOperation;
    int16_t queuedMusicLoops;
    int16_t queuedMusicFadeDuration;

};

#endif
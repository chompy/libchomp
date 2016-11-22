#ifndef CHOMP_SFX_H
#define CHOMP_SFX_H

#include <string>
#include <vector>
#include "../sdl_includes.h"
#include "../asset/asset.h"

#define MUSIC_STOP 0
#define MUSIC_PLAY 1
#define MUSIC_FADEIN 2
#define MUSIC_FADEOUT 3

#define MUSIC_LOAD_FAILED 0
#define MUSIC_LOAD_COMPLETE 1
#define MUSIC_LOAD_QUEUED 2

/**
 * Sound effect class.
 */
class ChompSfx {

public:

    /**
     * Music asset prefix.
     */
    static char MUSIC_ASSET_PREFIX[];

    /**
     * Constructor.
     */
    ChompSfx();

    /**
     * Destructor.
     */
    ~ChompSfx();

    /**
     * Load music file.
     * @param name Char array containing music filename
     * @return Status (MUSIC_LOAD_FAILED|MUSIC_LOAD_COMPLETE|MUSIC_LOAD_QUEUED)
     */
    uint8_t loadMusic(char* name);

    /**
     * Load music file and perform operation.
     * @param name Char array containing music filename
     * @param operation Operation to perform (MUSIC_STOP|MUSIC_PLAY|MUSIC_FADEIN|MUSIC_FADEOUT)
     * @return Status (MUSIC_LOAD_FAILED|MUSIC_LOAD_COMPLETE|MUSIC_LOAD_QUEUED)
     */
    uint8_t loadMusic(char* name, uint8_t operation);

    /**
     * Load music file and perform operation.
     * @param name Char array containing music filename
     * @param operation Operation to perform (MUSIC_STOP|MUSIC_PLAY|MUSIC_FADEIN|MUSIC_FADEOUT)
     * @param loops Number of times to loop music, -1 for infinite
     * @return Status (MUSIC_LOAD_FAILED|MUSIC_LOAD_COMPLETE|MUSIC_LOAD_QUEUED)
     */    
    uint8_t loadMusic(char* name, uint8_t operation, int16_t loops);

    /**
     * Load music file and perform operation.
     * @param name Char array containing music filename
     * @param operation Operation to perform (MUSIC_STOP|MUSIC_PLAY|MUSIC_FADEIN|MUSIC_FADEOUT)
     * @param loops Number of times to loop music, -1 for infinite
     * @param fadeDuration Time in milliseconds for fade in/out
     * @return Status (MUSIC_LOAD_FAILED|MUSIC_LOAD_COMPLETE|MUSIC_LOAD_QUEUED)
     */        
    uint8_t loadMusic(char* name, uint8_t operation, int16_t loops, int16_t fadeDuration);

    /**
     * Unload current music.
     */
    void unloadMusic();

    /**
     * Check to see if queue is ready to play next music.
     * Next music will play if ready.
     * @return True if queue is ready.
     */
    bool checkMusicQueue();

    /**
     * Change status of music.
     * @param operation Operation to perform (MUSIC_STOP|MUSIC_PLAY|MUSIC_FADEIN|MUSIC_FADEOUT)
     */
    void setMusic(uint8_t operation);

    /**
     * Change status of music.
     * @param operation Operation to perform (MUSIC_STOP|MUSIC_PLAY|MUSIC_FADEIN|MUSIC_FADEOUT)
     * @param loops Number of times to loop music, -1 for infinite
     */    
    void setMusic(uint8_t operation, int16_t loops);

    /**
     * Change status of music.
     * @param operation Operation to perform (MUSIC_STOP|MUSIC_PLAY|MUSIC_FADEIN|MUSIC_FADEOUT)
     * @param loops Number of times to loop music, -1 for infinite
     * @param fadeDuration Time in milliseconds for fade in/out
     */    
    void setMusic(uint8_t operation, int16_t loops, int16_t fadeDuration);
    
    /**
     * WIP!!
     * @TODO
     */
    void loadChunk(char* name);

    #ifndef WITHOUT_SDL_MIXER
    
    /**
     * SDL Mix Music
     */
    Mix_Music* music;
    
    #else

    /**
     * Null Music Pointer (if SDL Mixer not loaded)
     */
    void* music;

    #endif

protected:

    /**
     * Vector containing raw music data
     */
    std::vector<uint8_t> musicData;
    
    /**
     * String containing filename of queued music.
     */
    std::string queuedMusic;

    /**
     * Operation to peform on queued music.
     */
    uint8_t queuedMusicOperation;

    /**
     * Times to loop queued music.
     */
    int16_t queuedMusicLoops;

    /**
     * Fade duration of looped music.
     */
    int16_t queuedMusicFadeDuration;

};

#endif
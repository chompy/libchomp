#ifndef CHOMP_SFX_MUSIC_H
#define CHOMP_SFX_MUSIC_H

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

#define MUSIC_DEFAULT_FADE 0
#define MUSIC_DEFAULT_LOOPS -1

/**
 * Music player class.
 */
class ChompSfxMusic {

public:

    /**
     * Music asset prefix.
     */
    static char MUSIC_ASSET_PREFIX[];

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

    /**
     * Constructor.
     */
    ChompSfxMusic();

    /**
     * Destructor.
     */
    ~ChompSfxMusic();

    /**
     * Load music file.
     * @param name Char array containing music filename
     * @return Status (MUSIC_LOAD_FAILED|MUSIC_LOAD_COMPLETE|MUSIC_LOAD_QUEUED)
     */
    uint8_t loadMusic(const char* name);

    /**
     * Load music file and perform operation.
     * @param name Char array containing music filename
     * @param operation Operation to perform (MUSIC_STOP|MUSIC_PLAY|MUSIC_FADEIN|MUSIC_FADEOUT)
     * @return Status (MUSIC_LOAD_FAILED|MUSIC_LOAD_COMPLETE|MUSIC_LOAD_QUEUED)
     */
    uint8_t loadMusic(const char* name, uint8_t operation);

    /**
     * Load music file and perform operation.
     * @param name Char array containing music filename
     * @param operation Operation to perform (MUSIC_STOP|MUSIC_PLAY|MUSIC_FADEIN|MUSIC_FADEOUT)
     * @param loops Number of times to loop music, -1 for infinite
     * @return Status (MUSIC_LOAD_FAILED|MUSIC_LOAD_COMPLETE|MUSIC_LOAD_QUEUED)
     */    
    uint8_t loadMusic(const char* name, uint8_t operation, int16_t loops);

    /**
     * Load music file and perform operation.
     * @param name Char array containing music filename
     * @param operation Operation to perform (MUSIC_STOP|MUSIC_PLAY|MUSIC_FADEIN|MUSIC_FADEOUT)
     * @param loops Number of times to loop music, -1 for infinite
     * @param fadeDuration Time in milliseconds for fade in/out
     * @return Status (MUSIC_LOAD_FAILED|MUSIC_LOAD_COMPLETE|MUSIC_LOAD_QUEUED)
     */        
    uint8_t loadMusic(const char* name, uint8_t operation, int16_t loops, int16_t fadeDuration);

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
    void setMusic(uint8_t operation, int16_t loops, int32_t fadeDuration);

    /**
     * Convienence function that calls setMusic
     * with parameters to play loaded music.
     */
    void play() { setMusic(MUSIC_PLAY); }

    /**
     * Convienence function that calls setMusic
     * with parameters to stop playback of music.
     */
    void stop() { setMusic(MUSIC_STOP); }

    /**
     * Convienence function that calls setMusic
     * with parameters to fade in loaded music.
     * @param duration Time in ms for fade
     */
    void fadeIn(int32_t duration) { setMusic(MUSIC_FADEIN, MUSIC_DEFAULT_LOOPS, duration); }

    /**
     * Convienence function that calls setMusic
     * with parameters to fade out music.
     * @param duration Time in ms for fade
     */
    void fadeOut(int32_t duration) { setMusic(MUSIC_FADEOUT, MUSIC_DEFAULT_LOOPS, duration); }

    /**
     * Set volume to play music at.
     * @param volume Volume as a percentage (0=mute,100=max)
     */
    void setVolume(uint8_t volume);

    /**
     * Get volume music will play at.
     * @return Volume as a percentage (0=mute, 100=max)
     */
    uint8_t getVolume();

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
    int32_t queuedMusicFadeDuration;

};

#endif
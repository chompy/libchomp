#ifndef CHOMP_SFX_SAMPLE_H
#define CHOMP_SFX_SAMPLE_H

#include <string>
#include <vector>
#include "../sdl_includes.h"
#include "../asset/asset.h"

#define CHOMP_SFX_FAILED 200
#define CHOMP_SFX_STOP 0
#define CHOMP_SFX_PLAY 1
#define CHOMP_SFX_FADEIN 2
#define CHOMP_SFX_FADEOUT 3

#define CHOMP_SFX_DEFAULT_FADE 0
#define CHOMP_SFX_DEFAULT_TICKS -1

namespace Chomp
{

    /**
     * Sound effect sample player.
     */
    class SfxSample {

    public:

        /**
         * Sample asset prefix.
         */
        static char SAMPLE_ASSET_PREFIX[];

        #ifndef WITHOUT_SDL_MIXER
        
        /**
         * SDL Mix Chunk
         */
        Mix_Chunk* chunk;
        
        #else

        /**
         * Null chunk Pointer (if SDL Mixer not loaded)
         */
        void* chunk;

        #endif

        /**
         * Constructor.
         * @param name Name of asset
         */
        SfxSample(const char* name);

        /**
         * Destructor.
         */
        ~SfxSample();

        /**
         * Get channel this sample will play on.
         * @return Channel number
         */
        uint8_t getChannel() { return channel; }

        /**
         * Get status of sample.
         * @return Status code (SFX_FAILED|SFX_STOP|SFX_PLAY|SFX_FADEIN|SFX_FADEOUT)
         */
        uint8_t getStatus();

        /**
         * Change status of sample.
         * @param operation Operation to perform (SFX_STOP|SFX_PLAY|SFX_FADEIN|SFX_FADEOUT)
         */
        void setMode(uint8_t operation);

        /**
         * Change status of sample.
         * @param operation Operation to perform (SFX_STOP|SFX_PLAY|SFX_FADEIN|SFX_FADEOUT)
         * @param loops Number of times to loop sample (-1 for unlimited)
         */
        void setMode(uint8_t operation, int16_t loops);

        /**
         * Change status of sample.
         * @param operation Operation to perform (SFX_STOP|SFX_PLAY|SFX_FADEIN|SFX_FADEOUT)
         * @param loops Number of times to loop sample (-1 for unlimited)
         * @param fadeDuration Time in ms to fade for
         */
        void setMode(uint8_t operation, int16_t loops, int32_t fadeDuration);

        /**
         * Change status of sample.
         * @param operation Operation to perform (SFX_STOP|SFX_PLAY|SFX_FADEIN|SFX_FADEOUT)
         * @param loops Number of times to loop sample (-1 for unlimited)
         * @param fadeDuration Time in ms to fade for
         * @param ticks Max play length of sample
         */    
        void setMode(uint8_t operation, int16_t loops, int32_t fadeDuration, int32_t ticks);

        /**
         * Convienence function that calls setMode
         * with parameters to play sample.
         */
        void play() { setMode(CHOMP_SFX_PLAY); }

        /**
         * Convienence function that calls setMode
         * with parameters to stop sample.
         */
        void stop() { setMode(CHOMP_SFX_STOP); }

        /**
         * Convienence function that calls setMode
         * with parameters to fade in sample.
         * @param duration Time in ms to fade for
         */
        void fadeIn(int32_t duration) { setMode(CHOMP_SFX_FADEIN, 1, duration); }

        /**
         * Convienence function that calls setMode
         * with parameters to fade out sample.
         * @param duration Time in ms to fade for
         */
        void fadeOut(int32_t duration) { setMode(CHOMP_SFX_FADEOUT, 1, duration); }


        /**
         * Set volume to play sample at.
         * @param volume Volume as a percentage (0=mute,100=max)
         */
        void setVolume(uint8_t volume);

        /**
         * Get volume sample will play at.
         * @return Volume as a percentage (0=mute, 100=max)
         */
        uint8_t getVolume();

    protected:

        /**
         * Vector containing raw sample data
         */
        std::vector<uint8_t> sampleData;

        /**
         * Channel sample is to be played on.
         */
        int16_t channel;

        /**
         * Free currently loaded SDL chunk and stop playback.
         */
        void freeChunk();

    };
};

#endif
#ifndef CHOMP_SFX_SAMPLE_H
#define CHOMP_SFX_SAMPLE_H

#include <string>
#include <vector>
#include "../sdl_includes.h"
#include "../asset/asset.h"

#define SFX_FAILED 200
#define SFX_STOP 0
#define SFX_PLAY 1
#define SFX_FADEIN 2
#define SFX_FADEOUT 3

#define SFX_DEFAULT_FADE 0
#define SFX_DEFAULT_TICKS -1

/**
 * Sound effect sample player.
 */
class ChompSfxSample {

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
    ChompSfxSample(char* name);

    /**
     * Destructor.
     */
    ~ChompSfxSample();

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
    void setSample(uint8_t operation);

    /**
     * Change status of sample.
     * @param operation Operation to perform (SFX_STOP|SFX_PLAY|SFX_FADEIN|SFX_FADEOUT)
     * @param loops Number of times to loop sample (-1 for unlimited)
     */
    void setSample(uint8_t operation, int16_t loops);

    /**
     * Change status of sample.
     * @param operation Operation to perform (SFX_STOP|SFX_PLAY|SFX_FADEIN|SFX_FADEOUT)
     * @param loops Number of times to loop sample (-1 for unlimited)
     * @param fadeDuration Time in ms to fade for
     */
    void setSample(uint8_t operation, int16_t loops, int32_t fadeDuration);

    /**
     * Change status of sample.
     * @param operation Operation to perform (SFX_STOP|SFX_PLAY|SFX_FADEIN|SFX_FADEOUT)
     * @param loops Number of times to loop sample (-1 for unlimited)
     * @param fadeDuration Time in ms to fade for
     * @param ticks Max play length of sample
     */    
    void setSample(uint8_t operation, int16_t loops, int32_t fadeDuration, int32_t ticks);

    /**
     * Set volume to play sample at.
     * @param volume Volume as a percentage (0=mute,100=max)
     */
    void setSampleVolume(uint8_t volume);

    /**
     * Get volume sample will play at.
     * @return Volume as a percentage (0=mute, 100=max)
     */
    uint8_t getSampleVolume();

protected:

    /**
     * Vector containing raw sample data
     */
    std::vector<uint8_t> sampleData;

    /**
     * Channel sample is to be played on.
     */
    int16_t channel;

};

#endif
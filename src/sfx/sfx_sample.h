#ifndef CHOMP_SFX_SAMPLE_H
#define CHOMP_SFX_SAMPLE_H

#include <string>
#include <vector>
#include "../sdl_includes.h"
#include "../asset/asset.h"

#define SFX_STOP 0
#define SFX_PLAY 1
#define SFX_FADEIN 2
#define SFX_FADEOUT 3

#define SFX_DEFAULT_FADEIN 0
#define SFX_DEFAULT_FADEOUT 0
#define SFX_DEFAULT_TICKS -1

/**
 * Sound effect sample player.
 */
class ChompSfxSample {

public:

    /**
     * Constructor.
     * @param chunk SDL2 mixer chunk
     */
    ChompSfxSample(Mix_Chunk* chunk);

    /**
     * Get channel this sample will play on.
     * @return Channel number
     */
    uint8_t getChannel() { return channel; }

    void setSample(uint8_t operation);
    void setSample(uint8_t operation, int16_t loops);
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
     * Channel sample is to be played on.
     */
    uint16_t channel;

};

#endif
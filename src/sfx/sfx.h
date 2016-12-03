#ifndef CHOMP_SFX_H
#define CHOMP_SFX_H

#include <string>
#include <vector>
#include "../sdl_includes.h"
#include "../asset/asset.h"
#include "music.h"
#include "sfx_sample.h"

#define SFX_CHANNELS 64

/**
 * Sound effect class.
 */
class ChompSfx {

public:

    /**
     * Music player.
     */
    ChompSfxMusic music;

    /**
     * Constructor.
     */
    ChompSfx();

    /**
     * Destructor.
     */
    ~ChompSfx();
    
    /**
     * Load a sample for playback.
     * @param name Name of asset.
     * @return Sample playback object
     */
    ChompSfxSample loadSample(char* name);

protected:



};

#endif
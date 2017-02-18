#ifndef CHOMP_SFX_H
#define CHOMP_SFX_H

#include <string>
#include <vector>
#include "../sdl_includes.h"
#include "../asset/asset.h"
#include "music.h"
#include "sfx_sample.h"

#define CHOMP_SFX_CHANNELS 64

namespace Chomp
{

    /**
     * Sound effect class.
     */
    class Sfx {

    public:

        /**
         * Music player.
         */
        Chomp::SfxMusic music;

        /**
         * Constructor.
         */
        Sfx();

        /**
         * Destructor.
         */
        ~Sfx();
        
        /**
         * Load a sample for playback.
         * @param name Name of asset.
         * @return Sample playback object
         */
        SfxSample* loadSample(const char* name);

        /**
         * Stop and unload all samples.
         */
        void unloadAllSamples();

    protected:

        /**
         * Vector containing all loaded samples.
         */
        std::vector<Chomp::SfxSample> samples;

    };
};

#endif
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
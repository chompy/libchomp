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

#include "sfx.h"

Chomp::Sfx::Sfx()
{
    samples.clear();
    #ifndef WITHOUT_SDL_MIXER
    int flags = MIX_INIT_OGG;
    int initted = Mix_Init(MIX_INIT_OGG);
    if ((initted&flags) != flags) {
        std::string exceptionMsg = Mix_GetError();
        if (exceptionMsg.empty()) {
            exceptionMsg = "Failed to init SDL Mixer.";
        }
        throw Chomp::SdlMixerException(exceptionMsg);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096)==-1) {
        throw Chomp::SdlMixerException(Mix_GetError());   
    }
    Mix_AllocateChannels(CHOMP_SFX_CHANNELS);
    #endif
}

Chomp::Sfx::~Sfx()
{
    unloadAllSamples();
    #ifndef WITHOUT_SDL_MIXER
    music.unloadMusic();
    Mix_Quit();
    #endif
}

Chomp::SfxSample* Chomp::Sfx::loadSample(const char* name)
{
    samples.push_back( Chomp::SfxSample(name) );
    return &samples[samples.size() - 1];
}

void Chomp::Sfx::unloadAllSamples()
{
    #ifndef WITHOUT_SDL_MIXER
    Mix_HaltChannel(-1);
    #endif
    samples.clear();
}
#include "sfx.h"

ChompSfx::ChompSfx()
{
    int flags = MIX_INIT_OGG;
    int initted = Mix_Init(MIX_INIT_OGG);
    if (initted&flags != flags) {
        std::string exceptionMsg = Mix_GetError();
        if (exceptionMsg.empty()) {
            exceptionMsg = "Failed to init SDL Mixer.";
        }
        throw ChompSdlInitException(exceptionMsg);
    }

}

ChompSfx::~ChompSfx()
{
    Mix_Quit();
}
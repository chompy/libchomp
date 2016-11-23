#include "chomp.h"
uint32_t Chomp::lastFrameTime = 0;
float Chomp::targetFrameDelay = 0;

Chomp::Chomp()
{

    // init SDL2 events
    #ifndef EMSCRIPTEN
    SDL_SetMainReady();
    #endif
    if (SDL_Init(SDL_INIT_EVENTS) != 0) {
        throw ChompSdlException();
        return;
    }

}

Chomp::~Chomp()
{

}

void Chomp::start(ChompState* state)
{

    // set current state
    ChompState::changeState(state);

    // start main loop
    targetFrameDelay = 1000 / TARGET_FPS;
    lastFrameTime = 0;
    #ifdef EMSCRIPTEN
    emscripten_set_main_loop_arg(
        Chomp::emscriptenLoop,
        (void*) (&core),
        0,
        1
    );
    emscripten_set_main_loop_timing(EM_TIMING_RAF, 1);
    #else
    float delay = 0;
    while(Chomp::loop(&core)) {
        lastFrameTime = core.getTicks();
        delay = targetFrameDelay / core.deltaTime;
        if (delay > targetFrameDelay) {
            delay = targetFrameDelay;
        }
        if (delay > 0) {
            SDL_Delay( delay );
        }
    }
    #endif

    // end, uninit
    SDL_Quit();

}

void Chomp::emscriptenLoop(void* core)
{
    Chomp::loop((ChompCore*) core);
    ChompCore* _core = (ChompCore*) core;
    lastFrameTime = _core->getTicks();
}

bool Chomp::loop(ChompCore* core)
{
    // handle sdl events
    SDL_Event e;
    while( SDL_PollEvent(&e) ) {
        switch (e.type) {

            // process exit
            case SDL_QUIT:
            {
                // end main loop
                #ifdef EMSCRIPTEN
                emscripten_cancel_main_loop();
                #endif
                return false;
                break;         
            }

            // window events
            case SDL_WINDOWEVENT:
            {
                switch (e.window.event) {
                    // window resizes
                    case SDL_WINDOWEVENT_RESIZED:
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                    {
                        // todo
                        break;
                    }
                }
                break;
            }

            // input events
            case SDL_CONTROLLERAXISMOTION:
            case SDL_CONTROLLERBUTTONDOWN:
            case SDL_CONTROLLERBUTTONUP:
            case SDL_CONTROLLERDEVICEADDED:
            case SDL_CONTROLLERDEVICEREMOVED:
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEMOTION:
            case SDL_MOUSEWHEEL:
            {
                core->input.event(&e);
                break;
            }
        }
    }

    // tick
    ChompState::updateState();

    // draw
    core->gfx.render();

    // delta time
    core->deltaTime = ((float) core->getTicks() - (float) lastFrameTime) / (float) targetFrameDelay;
    if (core->deltaTime > 2) {
        core->deltaTime = 2;
    }

    // continue
    return true;

}
#include "chomp.h"

Chomp::Chomp()
{

    // init SDL2 events
    #ifndef EMSCRIPTEN
    SDL_SetMainReady();
    #endif
    if (SDL_Init(SDL_INIT_EVENTS) != 0) {
        throw ChompSdlInitException();
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
    int32_t targetFrameDelay = 1000 / TARGET_FPS;
    while( Chomp::loop(&core) ) { 
        int16_t deltaTime = (SDL_GetTicks() - lastFrameTime) / targetFrameDelay;
        if (targetFrameDelay - deltaTime >= 0) {
            SDL_Delay(targetFrameDelay - deltaTime);
        }
        lastFrameTime = SDL_GetTicks();
    }
    #endif

    // end, uninit
    SDL_Quit();

}

void Chomp::emscriptenLoop(void* core)
{
    Chomp::loop((ChompCore*) core);
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
            case SDL_JOYBUTTONDOWN:
            case SDL_JOYBUTTONUP:
            case SDL_JOYAXISMOTION:
            case SDL_JOYHATMOTION:
            case SDL_JOYDEVICEADDED:
            case SDL_JOYDEVICEREMOVED:
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEMOTION:
            case SDL_MOUSEWHEEL:
            {
                // todo
                break;
            }
        }
    }

    // tick
    ChompState::updateState();

    // draw
    core->gfx.render();

    // continue
    return true;

}
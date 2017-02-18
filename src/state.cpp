#include "state.h"

Chomp::State* Chomp::State::s_currentState = 0;

Chomp::State::State(Chomp::Core* _core)
{
    core = _core;
}

Chomp::State::~State()
{
    if (Chomp::State::s_currentState) {
        Chomp::State::s_currentState->exit();
    }
}

void Chomp::State::changeState(Chomp::State* s_currentState)
{
    if (Chomp::State::s_currentState) {
        Chomp::State::s_currentState->exit();
    }
    Chomp::State::s_currentState = s_currentState;
    if (Chomp::State::s_currentState) {
        Chomp::State::s_currentState->enter();
    }
}

void Chomp::State::updateState()
{
    if (Chomp::State::s_currentState) {
        Chomp::State::s_currentState->update();
    }
}

void Chomp::State::enter()
{

}

void Chomp::State::exit()
{

}

void Chomp::State::update()
{
    
}
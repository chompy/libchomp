#include "state.h"

ChompState* ChompState::s_currentState = 0;

ChompState::ChompState()
{

}

ChompState::~ChompState()
{

}

void ChompState::changeState(ChompState* s_currentState)
{
    if (ChompState::s_currentState) {
        ChompState::s_currentState->exit();
    }
    ChompState::s_currentState = s_currentState;
    if (ChompState::s_currentState) {
        ChompState::s_currentState->enter();
    }
}

void ChompState::enter()
{

}

void ChompState::exit()
{

}

void ChompState::update()
{
    
}
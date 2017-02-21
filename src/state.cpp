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
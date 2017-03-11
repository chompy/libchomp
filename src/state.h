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


#ifndef CHOMP_STATE_BASE
#define CHOMP_STATE_BASE

#include "core.h"

namespace Chomp
{

    /**
     * Libchomp State
     */
    class State
    {
    public:

        /**
         * Constructor.
         * @param _core Core object
         */
        State(Chomp::Core* _core);

        /**
         * Destructor.
         */
        virtual ~State();

        /**
         * Change active state.
         * @param s_currentState State to change to
         */
        static void changeState(State* s_currentState);

        /**
         * Call update method of current active state.
         */
        static void updateCurrentState();

        /**
         * Call resize method of current active state.
         */
        static void resizeCurrentState();

        /**
         * Called when state is made active.
         */
        virtual void enter();

        /**
         * Called when state is made inactive.
         */
        virtual void exit();

        /**
         * Called every frame state is active.
         */
        virtual void update();

        /**
         * Called when main windows is resized.
         */
        virtual void resize();

    protected:

        /**
         * Current active state.
         */
        static State* s_currentState;

        /**
         * Core object.
         */
        Chomp::Core* core;

    };
};

#endif
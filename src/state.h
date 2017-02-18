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
        static void updateState();

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
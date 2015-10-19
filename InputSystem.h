#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "EventListener.h"
#include "Dispatcher.h"
#include "Events.h"

#include "ComponentList.h"
#include "InputPlayer.h"

#include "Timer.h"

class InputSystem
{
    using Listener = EventListener<KeyPressed, SetPlayable, Play, Collided>;

    public:
        InputSystem(Dispatcher& dispatcher);

        void update();

    private:
        Dispatcher& dispatcher_;
        Listener listener_;
        Timer timer_;

        Entity active_;
        ComponentList<InputPlayer> players_;

        bool jumping_;
};

#endif // INPUTSYSTEM_H

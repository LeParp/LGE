#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <map>

#include "EventListener.h"
#include "Events.h"

#include "InputPlayer.h"

class Dispatcher;
class InputSystem
{
    using Listener = EventListener<SetPlayable, Play>;

    public:
        InputSystem(Dispatcher& dispatcher);

        void update();

    private:
        Dispatcher& dispatcher_;
        Listener listener_;

        unsigned active_player_;
        std::map<unsigned, InputPlayer> players_;
};

#endif // INPUTSYSTEM_H

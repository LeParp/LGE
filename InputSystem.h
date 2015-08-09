#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <memory>

#include "EventListener.h"
#include "Events.h"

#include "Controller.h"

class Dispatcher;
class InputSystem
{
    using Listener = EventListener<PlayerAdded>;

    public:
        InputSystem(Dispatcher& dispatcher);

        void update();

    private:
        Dispatcher& dispatcher_;
        Listener listener_;

        Controller controller_;
};

#endif // INPUTSYSTEM_H

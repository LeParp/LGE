#ifndef UISYSTEM_H
#define UISYSTEM_H

#include "EventListener.h"
#include "Events.h"

#include <SFML/Window/Window.hpp>

class Dispatcher;

class UISystem
{
    using Listener = EventListener<GameStarted>;

    public:
        UISystem(Dispatcher& dispatcher);

        void update();
        void display();

        bool running();

    private:
        Dispatcher& dispatcher_;
        Listener listener_;

        sf::Window window_;
        bool running_;
};

#endif // UISYSTEM_H

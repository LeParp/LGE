#ifndef UISYSTEM_H
#define UISYSTEM_H

#include "EventListener.h"
#include "Dispatcher.h"
#include "Events.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>

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

        sf::RenderWindow window_;
        bool running_;

        //Menu menu_;
        sf::Font font_;
};

#endif // UISYSTEM_H

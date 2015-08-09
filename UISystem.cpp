#include "UISystem.h"

#include "Dispatcher.h"

#include <SFML/Window/Event.hpp>

#ifdef NDEBUG
#define STYLE Fullscreen
#else
#define STYLE Default
#endif // NDEBUG

UISystem::UISystem(Dispatcher& dispatcher) :
    dispatcher_(dispatcher),
    window_(sf::VideoMode::getFullscreenModes()[0], "OpenGL", sf::Style::STYLE, sf::ContextSettings(24, 8, 4, 3, 3)),
    running_(true)
{
    dispatcher_.attach(listener_);

    window_.setVerticalSyncEnabled(true);
    window_.setMouseCursorVisible(false);

    listener_.log<GameStarted>([this](GameStarted const& event)
        {
            dispatcher_.emit(WindowCreated(window_.getSize().x, window_.getSize().y));
        });
}

void UISystem::update()
{
    sf::Event event;
    while(window_.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            running_ = false;
        }

        else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            running_ = false;
        }

        else if(event.type == sf::Event::Resized)
        {
            dispatcher_.emit(WindowResized(event.size.width, event.size.height));
        }
    }
}

void UISystem::display()
{
    window_.display();
}

bool UISystem::running()
{
    return running_;
}

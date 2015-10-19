#include "UISystem.h"

#include <chrono>
#include <stdexcept>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

#ifdef NDEBUG
#define STYLE sf::Style::Fullscreen
#else
#define STYLE sf::Style::Default
#endif // NDEBUG

#include "Dispatcher.h"

UISystem::UISystem(Dispatcher& dispatcher) :
    dispatcher_(dispatcher),
    window_(sf::VideoMode::getFullscreenModes()[0], "OpenGL", STYLE, sf::ContextSettings(24, 8, 4, 3, 3)),
    running_(true)
{
    dispatcher_.attach(listener_);

    window_.setVerticalSyncEnabled(true);
    window_.setMouseCursorVisible(false);

    if(!font_.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf"))
        throw std::runtime_error("Unable to load Arial font.");

    listener_.log<GameStarted>([this](const GameStarted& event) {
        dispatcher_.emit(WindowCreated{window_.getSize().x, window_.getSize().y});
    });
}

void UISystem::update()
{
    sf::Event event;
    while(window_.pollEvent(event))
    {
        if(event.type == sf::Event::Closed) {
            running_ = false;
        }

        else if(event.type == sf::Event::Resized) {
            dispatcher_.emit(WindowResized{event.size.width, event.size.height});
        }

        else if(event.type == sf::Event::KeyPressed) {
            if(event.key.code == sf::Keyboard::Escape)
                running_ = false;

            else
                dispatcher_.emit(KeyPressed{event.key.code});
        }
    }
}

void UISystem::display()
{
    sf::Text text("Binjour", font_);

    window_.resetGLStates();
    window_.draw(text);

    window_.display();
}

bool UISystem::running()
{
    return running_;
}

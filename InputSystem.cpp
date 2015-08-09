#include "InputSystem.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Dispatcher.h"

const sf::Vector2i mouse_pos(400, 400);
const float mouse_sensibility = 1.0 / 200.0;
const float movement_speed = 0.05;

InputSystem::InputSystem(Dispatcher& dispatcher) :
    dispatcher_(dispatcher)
{
    dispatcher_.attach(listener_);

    listener_.log<PlayerAdded>([this](PlayerAdded const& event)
        {
            controller_.set_player(event.player);
        });

    sf::Mouse::setPosition(mouse_pos);
}

void InputSystem::update()
{
    glm::vec2 rotation;

    rotation.x = (mouse_pos.x - sf::Mouse::getPosition().x) * mouse_sensibility;
    rotation.y = (mouse_pos.y - sf::Mouse::getPosition().y) * mouse_sensibility;

    controller_.rotate(rotation);


    glm::vec2 movement;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        movement.x += -movement_speed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += movement_speed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        movement.y += -movement_speed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement.y += movement_speed;

    controller_.move(movement);


    sf::Mouse::setPosition(mouse_pos);
}

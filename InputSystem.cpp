#include "InputSystem.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <glm/vec2.hpp>
#include <glm/gtx/normalize_dot.hpp>

#include "Dispatcher.h"

const sf::Vector2i mouse_pos(400, 400);
const float mouse_sensibility = 1.0 / 200.0;
const float movement_speed = 0.1;

InputSystem::InputSystem(Dispatcher& dispatcher) :
    dispatcher_(dispatcher),
    active_player_(0)
{
    dispatcher_.attach(listener_);

    listener_.log<SetPlayable>([this](SetPlayable const& event)
        {
            players_.insert({event.entity_id, InputPlayer(event.body, event.vertical_rotor, event.horizontal_rotor)});
        });

    listener_.log<Play>([this](Play const& event)
        {
            active_player_ = event.entity_id;
        });

    sf::Mouse::setPosition(mouse_pos);
}

void InputSystem::update()
{
    assert(players_.find(active_player_) != players_.end());
    InputPlayer& player = players_.at(active_player_);


    glm::vec2 rotation;

    rotation.x = (mouse_pos.x - sf::Mouse::getPosition().x) * mouse_sensibility;
    rotation.y = (mouse_pos.y - sf::Mouse::getPosition().y) * mouse_sensibility;

    player.rotate(rotation);


    glm::vec2 movement;

    movement.x -= sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    movement.x += sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    movement.y -= sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
    movement.y += sf::Keyboard::isKeyPressed(sf::Keyboard::S);

    if(glm::length(movement) != 0.0)
        movement = glm::normalize(movement) * movement_speed;

    player.move(movement);


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        dispatcher_.emit(ApplyForce({active_player_, {0.0, 3.0, 0.0}}));


    sf::Mouse::setPosition(mouse_pos);
}

#include "InputSystem.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <glm/vec2.hpp>
#include <glm/gtx/normalize_dot.hpp>

#include "Dispatcher.h"

const sf::Vector2i mouse_pos(400, 400);
const float mouse_sensibility = 0.1;
const float movement_speed = 8.0;

InputSystem::InputSystem(Dispatcher& dispatcher) :
    dispatcher_(dispatcher),
    jumping_(false)
{
    dispatcher_.attach(listener_);

    listener_.log<SetPlayable>([this](const SetPlayable& event) {
        players_.insert(event.entity, InputPlayer(event.body, event.vertical_rotor, event.horizontal_rotor));
    });

    listener_.log<Play>([this](const Play& event) {
        active_ = event.entity;
    });

    sf::Mouse::setPosition(mouse_pos);
}

void InputSystem::update()
{
    assert(!active_.is_null() && players_.has_value(active_));
    InputPlayer& player = players_[active_];

    double elapsed = timer_.elapsed();


    glm::vec2 input_rotation;

    input_rotation.x = (mouse_pos.x - sf::Mouse::getPosition().x);
    input_rotation.y = (mouse_pos.y - sf::Mouse::getPosition().y);

    sf::Mouse::setPosition(mouse_pos);

    player.rotate(input_rotation * glm::vec2(mouse_sensibility) * glm::vec2(elapsed));


    glm::vec2 input_movement;

    input_movement.x -= sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    input_movement.x += sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    input_movement.y -= sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
    input_movement.y += sf::Keyboard::isKeyPressed(sf::Keyboard::S);

    if(glm::length(input_movement) > 1.0)
        input_movement = glm::normalize(input_movement);

    player.move(input_movement * glm::vec2(movement_speed) * glm::vec2(elapsed));


    for(const auto& key_pressed : listener_.events<KeyPressed>())
    {
        if(key_pressed.key == Key::Space && !jumping_) {
            dispatcher_.emit(Impulse{active_, {0.0, 800.0, 0.0}});
            jumping_ = true;
        }
    }

    for(const auto& collided : listener_.events<Collided>())
    {
        if(collided.entity == active_) {
            jumping_ = false;
        }
    }

    listener_.clear_all();
}

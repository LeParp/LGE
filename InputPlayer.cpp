#include "InputPlayer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Player.h"

// Vitesse de rotation du body par rapport à sa vitesse de mouvement
const float body_rotation_speed = 1.0;

// Angle minimal entre la direction de la caméra et celle du rotor vertical
const float min_up_angle = 90.0;
const float min_down_angle = 15.0;

InputPlayer::InputPlayer(Node& body, Node& vertical_rotor, Node& horizontal_rotor) :
    body_(body),
    vertical_rotor_(vertical_rotor), // Rotor vertical autour duquel tournent la caméra et le body
    horizontal_rotor_(horizontal_rotor), // Rotor horizontal autour duquel tourne la caméra
    rotation_latency_(0.0)
{

}


void InputPlayer::move(glm::vec2 movement)
{
    // Déplacement du player
    vertical_rotor_.move({movement.x, 0.0, movement.y});

    // Rotation incrémentielle du body pour revenir à l'orientation du rotor vertical
    if(movement.x != 0.0 || movement.y != 0.0)
    {
        const float rotation_speed = body_rotation_speed * glm::length(movement);

        if(rotation_latency_ > rotation_speed)
        {
            body_.rotate({0.0, 1.0, 0.0}, rotation_speed);
            rotation_latency_ -= rotation_speed;
        }

        else if(rotation_latency_ < -rotation_speed)
        {
            body_.rotate({0.0, 1.0, 0.0}, -rotation_speed);
            rotation_latency_ += rotation_speed;
        }

        else
        {
            body_.rotate({0.0, 1.0, 0.0}, rotation_latency_);
            rotation_latency_ = 0.0;
        }
    }
}

void InputPlayer::rotate(glm::vec2 rotation)
{
    vertical_rotor_.rotate({0.0, 1.0, 0.0}, rotation.x);
    body_.rotate({0.0, 1.0, 0.0}, -rotation.x); // Le cube ne tourne pas dans le repère absolu

    // On sauvegarde l'angle le plus court vers l'orientation du rotor
    rotation_latency_ += rotation.x;
    while(rotation_latency_ > glm::radians(180.0))
        rotation_latency_ -= glm::radians(360.0);
    while(rotation_latency_ < glm::radians(-180.0))
        rotation_latency_ += glm::radians(360.0);

    // Vérification des limites de rotation par rapport à l'axe horizontal
    glm::vec3 forward = horizontal_rotor_.orientation({0.0, 0.0, -1.0}); // Direction actuelle de la vue

    if(rotation.y > 0.0)
    {
        glm::vec3 rotor_up = vertical_rotor_.orientation({0.0, 1.0, 0.0});

        // Le mouvement s'arrête lorsque l'angle entre la verticale (haut) et la direction de la caméra est inférieur à min_up_angle
        rotation.y = glm::min(rotation.y, glm::angle(forward, rotor_up) - glm::radians(min_up_angle));
    }

    else if(rotation.y < 0.0)
    {
        glm::vec3 rotor_down = vertical_rotor_.orientation({0.0, -1.0, 0.0});

        // Le mouvement s'arrête lorsque l'angle entre la verticale (bas) et la direction de la caméra est inférieur à min_down_angle
        rotation.y = glm::max(rotation.y, -(glm::angle(forward, rotor_down) - glm::radians(min_down_angle)));
    }

    horizontal_rotor_.rotate({1.0, 0.0, 0.0}, rotation.y);
}

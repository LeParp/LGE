#include "InputPlayer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Player.h"
#include "Camera.h"
#include "Node.h"

// Angle minimal entre la direction de la caméra et celle du rotor vertical
const float min_up_angle = 80.0;
const float min_down_angle = 2.5;

InputPlayer::InputPlayer(Player& player) :
    body_(player.mesh()),
    camera_(player.camera()),
    horizontal_rotor_(camera_.parent()), // Rotor horizontal autour duquel tourne la caméra
    vertical_rotor_(horizontal_rotor_.parent()), // Rotor vertical autour duquel tournent la caméra et le body
    rotation_delay_(0)
{

}


void InputPlayer::move(glm::vec2 movement)
{
    // Déplacement du player
    vertical_rotor_.move({movement.x, 0.0, movement.y});

    // Rotation incrémentielle du body pour revenir à l'orientation du rotor vertical
    if(movement.x != 0.0 || movement.y != 0.0)
    {
        if(rotation_delay_ > 0.1)
        {
            body_.rotate({0.0, 1.0, 0.0}, 0.1);
            rotation_delay_ -= 0.1;
        }

        else if(rotation_delay_ < -0.1)
        {
            body_.rotate({0.0, 1.0, 0.0}, -0.1);
            rotation_delay_ += 0.1;
        }

        else
        {
            body_.rotate({0.0, 1.0, 0.0}, rotation_delay_);
            rotation_delay_ = 0.0;
        }
    }
}

void InputPlayer::rotate(glm::vec2 rotation)
{
    vertical_rotor_.rotate({0.0, 1.0, 0.0}, rotation.x);
    body_.rotate({0.0, 1.0, 0.0}, -rotation.x); // Le cube ne tourne pas dans le repère absolu

    // On sauvegarde l'angle le plus court vers l'orientation du rotor
    rotation_delay_ += rotation.x;
    while(rotation_delay_ >= glm::radians(180.0))
        rotation_delay_ -= glm::radians(360.0);
    while(rotation_delay_ <= glm::radians(-180.0))
        rotation_delay_ += glm::radians(360.0);

    // Vérification des limites de rotation par rapport à l'axe horizontal
    glm::mat4 new_mat = glm::rotate(glm::inverse(camera_.view()), rotation.y, {1.0, 0.0, 0.0});
    glm::mat4 rotor_mat = vertical_rotor_.model();

    glm::vec3 new_forward = glm::vec3(new_mat * glm::vec4(0.0, 0.0, -1.0, 0.0)); // Direction de la vue après rotation
    glm::vec3 rotor_back = glm::vec3(rotor_mat * glm::vec4(0.0, 0.0, 1.0, 0.0));

    if(rotation.y > 0.0)
    {
        glm::vec3 rotor_up = glm::vec3(rotor_mat * glm::vec4(0.0, 1.0, 0.0, 0.0));

        if(glm::angle(new_forward, rotor_up) <= glm::radians(min_up_angle) || // Empêche que le regard de la caméra ne monte
           glm::angle(new_forward, rotor_back) <= glm::radians(90.0)) // Empêche le retournement de la caméra
            rotation.y = 0.0;
    }

    else if(rotation.y < 0.0)
    {
        glm::vec3 rotor_down = glm::vec3(rotor_mat * glm::vec4(0.0, -1.0, 0.0, 0.0));

        if(glm::angle(new_forward, rotor_down) <= glm::radians(min_down_angle) || // Empêche que le regard de la caméra ne descende
           glm::angle(new_forward, rotor_back) <= glm::radians(90.0)) // Empêche le retournement de la caméra
            rotation.y = 0.0;
    }

    horizontal_rotor_.rotate({1.0, 0.0, 0.0}, rotation.y);
}

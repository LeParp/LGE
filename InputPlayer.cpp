#include "InputPlayer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Player.h"
#include "Camera.h"
#include "Node.h"

const float min_angle = 2.5;

InputPlayer::InputPlayer(Player& player) :
    player_(player),
    camera_(player_.camera()),
    camera_parent_(camera_.parent())
{

}


void InputPlayer::move(glm::vec2 movement)
{
    camera_parent_.move({movement.x, 0.0, movement.y});
}

void InputPlayer::rotate(glm::vec2 rotation)
{
    camera_parent_.rotate({0.0, 1.0, 0.0}, rotation.x);

    // Vérification de la rotation pour ne pas retourner la caméra par le haut ou le bas
    glm::mat4 new_mat = glm::rotate(glm::inverse(camera_.view()), rotation.y, {1.0, 0.0, 0.0}); // Nouvelle matrice "model" de la camera après rotation
    glm::mat4 parent_mat = camera_parent_.model();

    glm::vec3 new_forward = glm::vec3(new_mat * glm::vec4(0.0, 0.0, -1.0, 0.0));  // Direction de la vue après rotation
    glm::vec3 parent_back = glm::vec3(parent_mat * glm::vec4(0.0, 0.0, 1.0, 0.0));

    if(rotation.y > 0.0)
    {
        glm::vec3 parent_up = glm::vec3(parent_mat * glm::vec4(0.0, 1.0, 0.0, 0.0));

        if(glm::angle(new_forward, parent_up) <= glm::radians(min_angle) ||
           glm::angle(new_forward, parent_back) <= glm::radians(90.0))
            return;
    }

    else if(rotation.y < 0.0)
    {
        glm::vec3 parent_down = glm::vec3(parent_mat * glm::vec4(0.0, -1.0, 0.0, 0.0));

        if(glm::angle(new_forward, parent_down) <= glm::radians(min_angle) ||
           glm::angle(new_forward, parent_back) <= glm::radians(90.0))
            return;
    }

    camera_.rotate({1.0, 0.0, 0.0}, rotation.y);
}

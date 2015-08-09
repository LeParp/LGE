#ifndef INPUTPLAYER_H
#define INPUTPLAYER_H

#include <glm/vec2.hpp>

class Player;
class Mesh;
class Camera;
class Node;

class InputPlayer
{
    public:
        InputPlayer(Player& player);

        void move(glm::vec2 movement);
        void rotate(glm::vec2 rotation);

    private:
        Mesh& body_;
        Camera& camera_;
        Node& horizontal_rotor_;
        Node& vertical_rotor_;

        float rotation_delay_;
};

#endif // INPUTPLAYER_H

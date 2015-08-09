#ifndef INPUTPLAYER_H
#define INPUTPLAYER_H

#include <glm/vec2.hpp>

class Player;
class Camera;
class Node;

class InputPlayer
{
    public:
        InputPlayer(Player& player);

        void move(glm::vec2 movement);
        void rotate(glm::vec2 rotation);

    private:
        Player& player_;
        Camera& camera_; // Tourne autour de l'axe horizontal
        Node& camera_parent_; // Tourne autour de l'axe vertical
};

#endif // INPUTPLAYER_H

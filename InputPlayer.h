#ifndef INPUTPLAYER_H
#define INPUTPLAYER_H

#include <glm/vec2.hpp>

class Node;
class InputPlayer
{
    public:
        InputPlayer(Node& body, Node& vertical_rotor, Node& horizontal_rotor);

        void move(glm::vec2 movement);
        void rotate(glm::vec2 rotation);

    private:
        Node& body_;
        Node& vertical_rotor_;
        Node& horizontal_rotor_;

        float rotation_delay_;
};

#endif // INPUTPLAYER_H

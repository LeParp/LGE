#ifndef INPUTPLAYER_H
#define INPUTPLAYER_H

#include <glm/vec2.hpp>

#include "Node.h"

class InputPlayer
{
    public:
        InputPlayer(Node& body, Node& vertical_rotor, Node& horizontal_rotor);

        void move(glm::vec2 input_movement);
        void rotate(glm::vec2 input_rotation);

        void jump();
        void landed();

    private:
        Node& body_;
        Node& vertical_rotor_;
        Node& horizontal_rotor_;

        bool jumping_;
        double rotation_latency_;
};

#endif // INPUTPLAYER_H

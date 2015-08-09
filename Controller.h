#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>

#include "InputPlayer.h"

class Controller
{
    public:
        void move(glm::vec2 movement);
        void rotate(glm::vec2 rotation);

        void set_player(Player& player);

    private:
        std::unique_ptr<InputPlayer> player_;
};

#endif // CONTROLLER_H

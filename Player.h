#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Model.h"
#include "Camera.h"

class Player : public Character
{
    public:
        Player(Model&& model);

        Camera& camera();
        Camera const& camera() const;

    private:
        Camera camera_;
        Node vertical_rotor_, horizontal_rotor_;
};

#endif // PLAYER_H

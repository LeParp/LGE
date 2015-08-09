#include "Controller.h"

void Controller::move(glm::vec2 movement)
{
    assert(player_);
    player_->move(movement);
}

void Controller::rotate(glm::vec2 rotation)
{
    assert(player_);
    player_->rotate(rotation);
}


void Controller::set_player(Player& player)
{
    player_ = std::make_unique<InputPlayer>(player);
}

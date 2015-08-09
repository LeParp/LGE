#include "Player.h"

Player::Player(Model&& model) :
    Character(model.get_mesh("Body"))
{
    camera_ = model.get_camera("Camera");
    camera_parent_ = model.get_node("Camera_parent");
}


Camera& Player::camera()
{
    return camera_;
}

Camera const& Player::camera() const
{
    return camera_;
}

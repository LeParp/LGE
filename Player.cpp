#include "Player.h"

Player::Player(Model&& model) :
    Character(model.get_mesh("Body")),
    camera_(model.get_camera("Camera")),
    vertical_rotor_(model.get_node("Vertical_rotor")),
    horizontal_rotor_(model.get_node("Horizontal_rotor"))
{

}


Camera& Player::camera()
{
    return camera_;
}

Camera const& Player::camera() const
{
    return camera_;
}

Node& Player::vertical_rotor()
{
    return vertical_rotor_;
}

Node& Player::horizontal_rotor()
{
    return horizontal_rotor_;
}

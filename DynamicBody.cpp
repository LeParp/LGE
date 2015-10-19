#include "DynamicBody.h"

#include "Mesh.h"

DynamicBody::DynamicBody(Mesh& mesh, Node& node) :
    mesh_(mesh),
    node_(node),
    mass_(80.0),
    velocity_(0.0, 0.0, 0.0)
{

}

void DynamicBody::impulse(glm::vec3 const& amount)
{
    velocity_ += amount;
}


float DynamicBody::mass()
{
    return mass_;
}

glm::vec3 DynamicBody::velocity()
{
    return velocity_;
}

glm::vec3 DynamicBody::position()
{
    return mesh_.position();
}


void DynamicBody::move(float time)
{
    node_.move((time * velocity_) / mass_);
}

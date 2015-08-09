#include "Light.h"

glm::vec3 Light::position() const
{
    return glm::vec3(model() * glm::vec4(0.0, 0.0, 0.0, 1.0));
}


glm::vec3& Light::color()
{
    return color_;
}

glm::vec3 const& Light::color() const
{
    return color_;
}


glm::vec3& Light::attenuations()
{
    return attenuations_;
}

glm::vec3 const& Light::attenuations() const
{
    return attenuations_;
}

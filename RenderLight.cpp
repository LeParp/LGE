#include "RenderLight.h"

RenderLight::RenderLight(Light const& light) :
    light_(light)
{

}

glm::vec3 RenderLight::position() const
{
    return light_.position();
}

glm::vec3 RenderLight::color() const
{
    return light_.color();
}

glm::vec3 RenderLight::attenuations() const
{
    return light_.attenuations();
}


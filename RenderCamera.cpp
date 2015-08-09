#include "RenderCamera.h"

RenderCamera::RenderCamera(Camera const& camera) :
    camera_(camera)
{

}

glm::mat4 RenderCamera::view() const
{
    return camera_.view();
}

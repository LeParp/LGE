#include "Viewer.h"

glm::mat4 Viewer::view() const
{
    assert(camera_);
    return camera_->view();
}

void Viewer::set_camera(Camera const& camera)
{
    camera_ = std::make_unique<RenderCamera>(camera);
}

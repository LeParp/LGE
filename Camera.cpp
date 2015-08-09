#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::view() const
{
    return glm::inverse(model()) * view_;
}

void Camera::look_at(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
    view_ = glm::lookAt(eye, center, up);
}


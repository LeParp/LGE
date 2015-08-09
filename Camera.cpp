#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::view() const
{
    return glm::inverse(model()) * view_;
}


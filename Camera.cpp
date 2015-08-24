#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <iostream>

void Camera::look_at(glm::vec3 center, glm::vec3 up)
{
    assert(center != position());

    glm::vec3 center_dir = glm::normalize(center - position());
    glm::vec3 axis = glm::normalize(glm::cross(forward(), center_dir));

    double angle = glm::angle(forward(), center_dir);
    if(angle == 0.0)
        return;
    rotate(glm::inverse(glm::mat3(model())) * axis, angle);

    glm::vec3 right = glm::normalize(glm::cross(up, forward()));
    glm::vec3 intended_up = glm::normalize(glm::cross(forward(), right));

    angle = glm::angle(intended_up, Camera::up());
    axis = glm::normalize(glm::cross(Camera::up(), intended_up));
    if(angle == 0.0)
        return;
    rotate({0.0, 0.0, -1.0}, angle);
}


glm::mat4 Camera::view() const
{
    return glm::inverse(model());
}


glm::vec3 Camera::forward()
{
    return orientation({0.0, 0.0, -1.0});
}

glm::vec3 Camera::up()
{
    return orientation({0.0, 1.0, 0.0});
}

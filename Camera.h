#ifndef CAMERA_H
#define CAMERA_H

#include "Object.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera : public Object
{
    public:
        // Default LookAt is OpenGL's : ({0.0, 0.0, 0.0}, {0.0, 0.0, -1.0}, {0.0, 1.0, 0.0})
        using Object::Object;

        // Absolute coordinates to look at
        void look_at(glm::vec3 center, glm::vec3 up); // encore buggé...

        glm::mat4 view() const;

        glm::vec3 forward();
        glm::vec3 up();
};

#endif // CAMERA_H

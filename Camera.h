#ifndef CAMERA_H
#define CAMERA_H

#include "Object.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera : public Object
{
    public:
        using Object::Object;

        glm::mat4 view() const;

        void look_at(glm::vec3 eye, glm::vec3 center, glm::vec3 up);

    private:
        glm::mat4 view_;
};

#endif // CAMERA_H

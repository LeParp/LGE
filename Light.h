#ifndef LIGHT_H
#define LIGHT_H

#include "Object.h"

#include <glm/vec3.hpp>

class Light : public Object
{
    public:
        using Object::Object;

        glm::vec3 position() const;

        glm::vec3& color();
        glm::vec3 const& color() const;

        glm::vec3& attenuations();
        glm::vec3 const& attenuations() const;

    private:
        glm::vec3 color_;
        glm::vec3 attenuations_;
};

#endif // LIGHT_H

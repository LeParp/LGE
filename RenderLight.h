#ifndef RENDERLIGHT_H
#define RENDERLIGHT_H

#include "Light.h"

class RenderLight
{
    public:
        RenderLight(Light const& light);
        RenderLight(Light&& light) = delete;

        glm::vec3 position() const;
        glm::vec3 color() const;
        glm::vec3 attenuations() const;

    private:
        Light const& light_;
};

#endif // RENDERLIGHT_H

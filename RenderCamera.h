#ifndef RENDERCAMERA_H
#define RENDERCAMERA_H

#include "Camera.h"

class RenderCamera
{
    public:
        RenderCamera(const Camera& camera);
        RenderCamera(Camera&& camera) = delete;

        glm::mat4 view() const;

    private:
        Camera const& camera_;
};

#endif // RENDERCAMERA_H

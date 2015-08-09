#ifndef VIEWER_H
#define VIEWER_H

#include <memory>

#include "RenderCamera.h"

class Viewer
{
    public:
        glm::mat4 view() const;

        void set_camera(Camera const& camera);
        void set_camera(Camera&& camera) = delete;

    private:
        std::unique_ptr<RenderCamera> camera_;
};

#endif // VIEWER_H

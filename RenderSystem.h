#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <memory>
#include <vector>

#include "RenderContext.h"

#include "EventListener.h"
#include "Events.h"

#include "PhongShader.h"
#include "Viewer.h"
#include "RenderLight.h"
#include "RenderMesh.h"

class Dispatcher;
class RenderSystem : public RenderContext
{
    using Listener = EventListener<WindowCreated, WindowResized,
                                   MeshAdded, LightAdded, CameraAdded>;

    public:
        RenderSystem(Dispatcher& dispatcher);

        void render();

    private:
        void resize(unsigned width, unsigned height);

        Dispatcher& dispatcher_;
        Listener listener_;

        PhongShader shader_;
        glm::mat4 projection_;

        Viewer viewer_;
        std::vector<RenderLight> lights_;
        std::vector<RenderMesh> meshes_;
};

#endif // RENDERSYSTEM_H

#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "RenderContext.h"

#include "EventListener.h"
#include "Dispatcher.h"
#include "Events.h"

#include "ComponentList.h"
#include "PhongShader.h"
#include "RenderCamera.h"
#include "RenderLight.h"
#include "RenderMesh.h"

class RenderSystem : private RenderContext
{
    using Listener = EventListener<WindowCreated, WindowResized,
                                   SetRenderable, SetLighter, SetViewer,
                                   View>;

    public:
        RenderSystem(Dispatcher& dispatcher);

        void render();

    private:
        void resize(unsigned width, unsigned height);

        Dispatcher& dispatcher_;
        Listener listener_;

        PhongShader shader_;
        glm::mat4 projection_;

        Entity viewer_;
        ComponentList<RenderCamera> cameras_;
        ComponentList<RenderLight> lights_;
        ComponentList<RenderMesh> meshes_;
};

#endif // RENDERSYSTEM_H

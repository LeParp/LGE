#include "RenderSystem.h"

#include "Dispatcher.h"

#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>

RenderSystem::RenderSystem(Dispatcher& dispatcher) :
    dispatcher_(dispatcher),
    shader_(1)
{
    dispatcher_.attach(listener_);

    glEnable(GL_DEPTH_TEST);

    shader_.use();

    listener_.log<WindowCreated>([this](WindowCreated const& event)
        {
            resize(event.width, event.height);
        });

    listener_.log<WindowResized>([this](WindowResized const& event)
        {
            resize(event.width, event.height);
        });

    listener_.log<MeshAdded>([this](MeshAdded const& event)
        {
            meshes_.emplace_back(event.mesh);
        });

    listener_.log<LightAdded>([this](LightAdded const& event)
        {
            lights_.emplace_back(event.light);

            shader_ = PhongShader(lights_.size());
            shader_.use();
            shader_.projection(projection_);
        });

    listener_.log<CameraAdded>([this](CameraAdded const& event)
        {
            viewer_.set_camera(event.camera);
        });
}

void RenderSystem::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_.use();
    shader_.view(viewer_.view());
    for(size_t i = 0; i < lights_.size(); ++i)
        shader_.light(lights_[i], i);

    for(auto& mesh : meshes_)
    {
        shader_.material(mesh.material());
        shader_.model(mesh.model());
        mesh.render();
    }
}

void RenderSystem::resize(unsigned width, unsigned height)
{
    glViewport(0, 0, width, height);
    projection_ = glm::perspective(glm::radians(60.0), (double) width / height, 0.01, 50.0);
    shader_.projection(projection_);
}

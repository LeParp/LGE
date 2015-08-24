#include "RenderSystem.h"

#include "Dispatcher.h"

#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>

RenderSystem::RenderSystem(Dispatcher& dispatcher) :
    dispatcher_(dispatcher),
    shader_(1),
    active_camera(0)
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

    listener_.log<SetRenderable>([this](SetRenderable const& event)
        {
            meshes_.emplace_back(event.mesh);
        });

    listener_.log<SetLighter>([this](SetLighter const& event)
        {
            lights_.emplace_back(event.light);

            shader_ = PhongShader(lights_.size());
            shader_.use();
            shader_.projection(projection_);
        });

    listener_.log<SetViewer>([this](SetViewer const& event)
        {
            cameras_.insert({event.entity_id, RenderCamera(event.camera)});
        });

    listener_.log<View>([this](View const& event)
        {
            active_camera = event.entity_id;
        });
}


void RenderSystem::render()
{
    assert(cameras_.find(active_camera) != cameras_.end());
    RenderCamera& camera = cameras_.at(active_camera);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_.use();
    shader_.view(camera.view());
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

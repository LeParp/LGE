#include "RenderSystem.h"

#include "Dispatcher.h"

#include <GL/glew.h>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

RenderSystem::RenderSystem(Dispatcher& dispatcher) :
    dispatcher_(dispatcher),
    shader_(1)
{
    dispatcher_.attach(listener_);

    glClearColor(0.2, 0.2, 0.8, 1.0);

    listener_.log<WindowCreated>([this](WindowCreated const& event) {
        resize(event.width, event.height);
    });

    listener_.log<WindowResized>([this](WindowResized const& event) {
        resize(event.width, event.height);
    });

    listener_.log<SetRenderable>([this](SetRenderable const& event) {
        meshes_.insert(event.entity, RenderMesh(event.mesh));
    });

    listener_.log<SetLighter>([this](SetLighter const& event) {
        lights_.insert(event.entity, RenderLight(event.light));

        shader_ = PhongShader(lights_.size());
        shader_.use();
        shader_.projection(projection_);
    });

    listener_.log<SetViewer>([this](SetViewer const& event) {
        cameras_.insert(event.entity, RenderCamera(event.camera));
    });

    listener_.log<View>([this](View const& event) {
        viewer_ = event.entity;
    });
}


void RenderSystem::render()
{
    assert(!viewer_.is_null() && cameras_.has_value(viewer_));
    RenderCamera& camera = cameras_[viewer_];

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_.use();
    shader_.view(camera.view());

    unsigned light_rank = 0;
    for(auto& light : lights_) {
        shader_.light(light, light_rank++);
    }

    for(auto& mesh : meshes_) {
        shader_.material(mesh.material());
        shader_.model(mesh.model());
        mesh.render();
    }
}


void RenderSystem::resize(unsigned width, unsigned height)
{
    glViewport(0, 0, width, height);
    projection_ = glm::perspective(glm::radians(60.0), (double) width / height, 0.01, 500.0);
    shader_.projection(projection_);
}

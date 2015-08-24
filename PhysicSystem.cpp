#include "PhysicSystem.h"

#include "Dispatcher.h"

PhysicSystem::PhysicSystem(Dispatcher& dispatcher) :
    dispatcher_(dispatcher)
{
    dispatcher_.attach(listener_);

    listener_.log<SetDynamicBody>([this](SetDynamicBody const& event)
        {
            meshes_.insert({event.entity_id, event.mesh});
        });

    listener_.log<SetGround>([this](SetGround const& event)
        {
            ground_.set_terrain(event.mesh);
        });

    listener_.log<ApplyForce>([this](ApplyForce const& event)
        {
            assert(meshes_.find(event.entity_id) != meshes_.end());
            meshes_.at(event.entity_id).apply(event.force);
        });
}

void PhysicSystem::update()
{
    for(auto it : meshes_)
    {
        auto entity_id = it.first;
        auto& mesh = it.second;
    }
}

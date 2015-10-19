#include "PhysicSystem.h"

#include "Dispatcher.h"
#include "Mesh.h"

PhysicSystem::PhysicSystem(Dispatcher& dispatcher) :
    dispatcher_(dispatcher)
{
    dispatcher_.attach(listener_);

    listener_.log<SetGround>([this](const SetGround& event) {
        grounds_.insert(event.entity, Ground(event.mesh));
    });

    listener_.log<SetDynamicBody>([this](const SetDynamicBody& event) {
        bodies_.insert(event.entity, DynamicBody(event.mesh, event.root));
    });

    listener_.log<Impulse>([this](const Impulse& event) {
        assert(bodies_.has_value(event.entity));
        bodies_[event.entity].impulse(event.amount);
    });
}

void PhysicSystem::update()
{
    for(auto it = bodies_.begin(); it != bodies_.end(); ++it)
    {
        auto& body = it.value();

        if(body.position().y > -1.0) {
            body.impulse({0.0, -15.0 * body.mass() / 60.0, 0.0});
        }

        else if(body.position().y <= -1.0 && body.velocity().y < 0.0) {
            body.impulse({0.0, -body.velocity().y + (-1.0 - body.position().y) * 1000.0, 0.0});
            dispatcher_.emit(Collided{it.key()});
        }

        body.move(1.0 / 60.0);
    }
}

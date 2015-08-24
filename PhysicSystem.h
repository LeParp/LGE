#ifndef PHYSICSYSTEM_H
#define PHYSICSYSTEM_H

#include <map>

#include "EventListener.h"
#include "Events.h"

#include "Ground.h"
#include "PhysicMesh.h"

class Dispatcher;
class PhysicSystem
{
    using Listener = EventListener<SetDynamicBody, SetGround, ApplyForce>;

    public:
        PhysicSystem(Dispatcher& dispatcher);

        void update();

    private:
        Dispatcher& dispatcher_;
        Listener listener_;

        Ground ground_;
        std::map<unsigned, PhysicMesh> meshes_;
};

#endif // PHYSICSYSTEM_H

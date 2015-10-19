#ifndef PHYSICSYSTEM_H
#define PHYSICSYSTEM_H

#include "EventListener.h"
#include "Dispatcher.h"
#include "Events.h"

#include "ComponentList.h"
#include "Ground.h"
#include "DynamicBody.h"

class PhysicSystem
{
    using Listener = EventListener<SetGround, SetDynamicBody, Impulse>;

    public:
        PhysicSystem(Dispatcher& dispatcher);

        void update();

    private:
        Dispatcher& dispatcher_;
        Listener listener_;

        ComponentList<Ground> grounds_;
        ComponentList<DynamicBody> bodies_;
};

#endif // PHYSICSYSTEM_H

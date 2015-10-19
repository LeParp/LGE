#ifndef GENERATORSYSTEM_H
#define GENERATORSYSTEM_H

#include <vector>

#include "EventListener.h"
#include "Dispatcher.h"
#include "Events.h"

#include "Loader.h"
#include "Entity.h"
#include "Model.h"

class GeneratorSystem
{
    using Listener = EventListener<GameStarted>;

    public:
        GeneratorSystem(Dispatcher& dispatcher);

        void update();

    private:
        Dispatcher& dispatcher_;
        Listener listener_;

        Loader loader_;
        EntitySeed entities_seed_;
        std::vector<Model> models_;
};

#endif // GENERATORSYSTEM_H

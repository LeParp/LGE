#ifndef GENERATORSYSTEM_H
#define GENERATORSYSTEM_H

#include <vector>

#include "EventListener.h"
#include "Events.h"

#include "Loader.h"
#include "Model.h"

class Dispatcher;

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
        std::vector<Model> models_;
        unsigned entities_seed_;
};

#endif // GENERATORSYSTEM_H

#ifndef GENERATORSYSTEM_H
#define GENERATORSYSTEM_H

#include <memory>

#include "EventListener.h"
#include "Events.h"

#include "Loader.h"
#include "Player.h"
#include "Terrain.h"

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
        Player player_;
        Terrain terrain_;
};

#endif // GENERATORSYSTEM_H

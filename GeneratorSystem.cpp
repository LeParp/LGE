#include "GeneratorSystem.h"

#include "Dispatcher.h"

GeneratorSystem::GeneratorSystem(Dispatcher& dispatcher) :
    dispatcher_(dispatcher),
    player_(loader_.load_model("player.mdl")),
    terrain_(loader_.load_model("terrain.mdl"))
{
    dispatcher_.attach(listener_);

    listener_.log<GameStarted>([this](GameStarted const& start_event)
        {
            dispatcher_.emit(PlayerAdded(player_));
            dispatcher_.emit(MeshAdded(player_.mesh()));
            dispatcher_.emit(CameraAdded(player_.camera()));

            dispatcher_.emit(MeshAdded(terrain_.mesh()));
            for(auto& light : terrain_.lights())
                dispatcher_.emit(LightAdded(light));
        });
}

void GeneratorSystem::update()
{

}

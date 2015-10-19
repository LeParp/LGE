#include "GeneratorSystem.h"

#include "Dispatcher.h"

GeneratorSystem::GeneratorSystem(Dispatcher& dispatcher) :
    dispatcher_(dispatcher)
{
    dispatcher_.attach(listener_);

    listener_.log<GameStarted>([this](const GameStarted& start_event) {
        {
            Entity new_entity{entities_seed_};

            models_.push_back(loader_.load_model("player.mdl"));
            Model& model = models_.back();

            dispatcher_.emit(SetRenderable{new_entity, model.mesh("Body")});
            dispatcher_.emit(SetDynamicBody{new_entity, model.mesh("Body"), model.node("Vertical_rotor")});
            dispatcher_.emit(SetViewer{new_entity, model.camera("Camera")});
            dispatcher_.emit(SetPlayable{new_entity,
                                         model.mesh("Body").node(),
                                         model.node("Vertical_rotor"),
                                         model.node("Horizontal_rotor")});

            dispatcher_.emit(View{new_entity});
            dispatcher_.emit(Play{new_entity});
        }

        {
            Entity new_entity{entities_seed_};

            models_.push_back(loader_.load_model("terrain.mdl"));
            Model& model = models_.back();

            dispatcher_.emit(SetRenderable{new_entity, model.mesh("Terrain")});
            dispatcher_.emit(SetGround{new_entity, model.mesh("Terrain")});
            for(Light& light : model.lights()) {
                dispatcher_.emit(SetLighter{new_entity, light});
            }
            models_.push_back(std::move(model));
        }
    });
}

void GeneratorSystem::update()
{

}

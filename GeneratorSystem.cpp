#include "GeneratorSystem.h"

#include "Dispatcher.h"

GeneratorSystem::GeneratorSystem(Dispatcher& dispatcher) :
    dispatcher_(dispatcher),
    entities_seed_(1)
{
    dispatcher_.attach(listener_);

    listener_.log<GameStarted>([this](GameStarted const& start_event)
        {
            {
                models_.push_back(loader_.load_model("player.mdl"));
                Model& model = models_.back();
                dispatcher_.emit(SetRenderable{entities_seed_, model.mesh("Body")});
                dispatcher_.emit(SetDynamicBody{entities_seed_, model.mesh("Body")});
                dispatcher_.emit(SetViewer{entities_seed_, model.camera("Camera")});
                dispatcher_.emit(SetPlayable{entities_seed_, model.mesh("Body").node(),
                                                             model.node("Vertical_rotor"),
                                                             model.node("Horizontal_rotor")});
            }

            dispatcher_.emit(View{entities_seed_});
            dispatcher_.emit(Play{entities_seed_});

            entities_seed_++;

            {
                models_.push_back(loader_.load_model("terrain.mdl"));
                Model& model = models_.back();
                dispatcher_.emit(SetRenderable{entities_seed_, model.mesh("Terrain")});
                dispatcher_.emit(SetGround{entities_seed_, model.mesh("Terrain")});
                for(Light& light : model.lights())
                    dispatcher_.emit(SetLighter{entities_seed_, light});
                models_.push_back(std::move(model));
            }
        });
}

void GeneratorSystem::update()
{

}

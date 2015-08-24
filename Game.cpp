#include "Game.h"

Game::Game() :
    ui_sys_(dispatcher_),
    generator_sys_(dispatcher_),
    input_sys_(dispatcher_),
    physic_sys_(dispatcher_),
    render_sys_(dispatcher_)
{

}

void Game::run()
{
    dispatcher_.emit(GameStarted());

    while(ui_sys_.running())
    {
        ui_sys_.update();
        generator_sys_.update();
        input_sys_.update();
        physic_sys_.update();
        render_sys_.render();
        ui_sys_.display();
    }
}

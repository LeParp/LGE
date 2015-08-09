#ifndef GAME_H
#define GAME_H

#include "Dispatcher.h"

#include "UISystem.h"
#include "GeneratorSystem.h"
#include "InputSystem.h"
#include "RenderSystem.h"

class Game
{
    public:
        Game();

        void run();

    private:
        Dispatcher dispatcher_;

        UISystem ui_sys_;
        GeneratorSystem generator_sys_;
        InputSystem input_sys_;
        RenderSystem render_sys_;
};

#endif // GAME_H

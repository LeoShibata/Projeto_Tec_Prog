#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

#include "Being.hpp"
#include "Managers/GraphicManager.hpp"
#include "Managers/EventManager.hpp"
#include "Stages/stage.hpp"


class Game {
    private:
        Managers::GraphicManager* pGraphic;
        Managers::EventManager* pEvent; 
        Stages::Stage* stage; 

    public:
        Game();
        ~Game();

        void run();
};

#endif

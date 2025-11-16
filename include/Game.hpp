#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

#include "Being.hpp"
#include "Managers/GraphicManager.hpp"
#include "Managers/EventManager.hpp"
#include "Stages/Graveyard.hpp"
#include "Stages/Castle.hpp"


class Game {
    private:
        Managers::GraphicManager* pGraphic;
        Managers::EventManager* pEvent; 
        Stages::Graveyard* graveyard;
        Stages::Castle* castle; 

    public:
        Game();
        ~Game();

        void run();
};

#endif

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

#include "Being.hpp"
#include "Managers/GraphicManager.hpp"
#include "Managers/EventManager.hpp"
#include "Stages/Graveyard.hpp"
#include "Stages/Castle.hpp"
#include "Managers/StateManager.hpp"


class Game {
    private:
        Managers::GraphicManager* pGraphic;
        Managers::EventManager* pEvent; 
        Managers::StateManager* pState;
        Stages::Graveyard* graveyard;
        Stages::Castle* castle; 

        
    public:
        Game();
        ~Game();

        void run();
};

#endif

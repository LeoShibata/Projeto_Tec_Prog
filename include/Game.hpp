#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

#include "Being.hpp"
#include "Managers/GraphicManager.hpp"
#include "Managers/EventManager.hpp"
#include "Stages/Stage1.hpp"
#include "Stages/BossRoom.hpp"


class Game {
    private:
        Managers::GraphicManager* pGraphic;
        Managers::EventManager* pEvent; 
        Stages::Stage1* stage1;
        Stages::BossRoom* stage2; 

    public:
        Game();
        ~Game();

        void run();
};

#endif

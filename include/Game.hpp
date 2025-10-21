#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>

#include <Managers/GraphicManager.hpp>
#include "Characters/Player.hpp"
#include "Characters/Character.hpp"

class Game {
    private:
        Managers::GraphicManager* pGraphic; 
        std::vector<Characters::Character*> characters;

    public:
        Game();
        ~Game();
        void run();
};

#endif
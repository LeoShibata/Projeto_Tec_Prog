#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

#include "Managers/GraphicManager.hpp"
#include "Managers/EventManager.hpp"
#include "Managers/CollisionManager.hpp"

#include "Being.hpp"
#include "List/EntityList.hpp"

class Game {
    private:
        Managers::GraphicManager* pGraphic;
        Managers::EventManager* pEvent; 
        Managers::CollisionManager* pCollision;

        List::EntityList* characterList;
        List::EntityList* obstacleList;

    public:
        Game();
        ~Game();
        void run();
};

#endif
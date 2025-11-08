#ifndef STAGE_HPP
#define STAGE_HPP


#include "Entities/Entity.hpp"
#include <iostream>

#include "Managers/GraphicManager.hpp"
#include "Managers/EventManager.hpp"
#include "Managers/CollisionManager.hpp"

#include "Being.hpp"
#include "List/EntityList.hpp"
#include "Entities/Characters/Player.hpp"
#include "Entities/Characters/Enemies/Enemies.hpp"
#include "Entities/Characters/Enemies/Spirit.hpp"
#include "Entities/Obstacles/Obstacle.hpp"
#include "Entities/Obstacles/Platform.hpp"

#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>



namespace Entities::Characters {
    class Stage : public Entity {

        protected:
            Managers::EventManager* pEvent; 
            Managers::CollisionManager* pCollision;

            List::EntityList* characterList;
            List::EntityList* obstacleList;
            string jsonPath;


        protected:

            void createSpirit();
            void createPlatform();
            void createPlayer();
            virtual void createEnemies() = 0;
            virtual void createObstacles () = 0;
        public:
    };
}

#endif
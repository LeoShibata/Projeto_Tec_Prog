#ifndef STAGE_HPP
#define STAGE_HPP

#include <iostream>

#include "Managers/GraphicManager.hpp"
#include "Managers/EventManager.hpp"
#include "Managers/CollisionManager.hpp"

#include "Being.hpp"
#include "List/EntityList.hpp"
#include "Entities/Characters/Player.hpp"
#include "Entities/Characters/Enemies/Enemies.hpp"
#include "Entities/Characters/Enemies/Spirit.hpp"
#include "Entities/Characters/Enemies/Skeleton.hpp"
#include "Entities/Obstacles/Obstacle.hpp"
#include "Entities/Obstacles/Platform.hpp"
#include "utils/json.hpp"

#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

namespace Stages {
    class Stage : public Being {
        protected:
            Managers::EventManager* pEvent; 
            Managers::CollisionManager* pCollision;
            Managers::GraphicManager* pGraphic;

            List::EntityList* characterList;
            List::EntityList* obstacleList;
            const int max_spirits;
            const int max_obstacles;
            static const int tileSize = 32;

        protected:
            void createPlayer(sf::Vector2f pos);
            void createPlatform(sf::Vector2f pos);
            void createSpirit(sf::Vector2f pos);    
            void createSkeleton(sf::Vector2f pos);
            //virtual void createEnemies() = 0;
            //virtual void createObstacles () = 0;
            virtual void createMap() = 0;

        public:
            Stage();
            virtual~Stage();
            
            void draw(sf::RenderWindow* window);
            void execute() override;
            
    };
}

#endif
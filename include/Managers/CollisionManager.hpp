#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <list>
#include "Entities/Characters/Enemies/Enemies.hpp"
#include "Entities/Characters/Player.hpp"
#include "Entities/Obstacles/Obstacle.hpp"

using namespace std;
namespace Managers {
    class CollisionManager {
        private:
            vector<Entities::Characters::Enemies*> lIs;
            Entities::Characters::Player* pPlayer;
            list<Entities::Obstacles::Obstacle*> lOs;


        public:
            CollisionManager();
            ~CollisionManager();
            void setPlayer(Entities::Characters::Player* pPlayer);
            void includeEntity(Entities::Entity* ent1);
            void removeEntity(Entities::Entity* ent1);
            const sf::Vector2f collisionDetection(Entities::Entity* ent1, Entities::Entity* ent2);
            void verifyPlayerEnemy();
            void verifyPlayerObstacle();
            void run();
    };
}

#endif
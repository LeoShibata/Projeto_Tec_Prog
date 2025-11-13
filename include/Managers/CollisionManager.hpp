#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <list>

#include "Entities/Characters/Player.hpp"
#include "Entities/Characters/Enemies/Enemies.hpp"
#include "Entities/Obstacles/Obstacle.hpp"
#include <iostream>
using namespace std;
    namespace Managers {
        class CollisionManager {
            //inspired by ASCENT https://github.com/0x4D4453/ASCENT/blob/main/include/Manager/Collision/CollisionManager.h
            enum class CollisionType {
                Vertical =0, //basically boolean type variable, but with better names to code
                Horizontal
            };
            struct CollisionData {
                CollisionType type;
                float ds;
                bool collided = 0;
            };

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
                
                const CollisionData collisionDetection(Entities::Entity* ent1, Entities::Entity* ent2);
                void verifyPlayerEnemy();
                void verifyPlayerObstacle();
                void verifyEnemyObstacle();

                void run();
        };
}

#endif
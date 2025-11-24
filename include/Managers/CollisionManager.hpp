#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP

#include "Entities/Projectile.hpp"
#include "Entities/Characters/Player.hpp"
#include "Entities/Characters/Enemies/Enemies.hpp"
#include "Entities/Obstacles/Obstacle.hpp"
#include "Entities/Floor.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <list>
#include <iostream>
#include <set>

namespace Managers {
    class CollisionManager {
        //inspired by ASCENT https://github.com/0x4D4453/ASCENT/blob/main/include/Manager/Collision/CollisionManager.h
        enum class CollisionType {
            Vertical = 0, //basically boolean type variable, but with better names to code
            Horizontal
        };
        struct CollisionData {
            CollisionType type;
            float ds;
            bool collided = 0;
        };

        private:
            std::vector<Entities::Characters::Enemies*> lIs;
            std::list<Entities::Obstacles::Obstacle*> lOs;
            std::list<Entities::Floor*> lFs;
            std::set<Entities::Projectile*> lPs;
            Entities::Characters::Player* pPlayer1;
            Entities::Characters::Player* pPlayer2;


        public:
            CollisionManager();
            ~CollisionManager();
            void setPlayer1(Entities::Characters::Player* pPlayer);
            void setPlayer2(Entities::Characters::Player* pPlayer);
            void includeEntity(Entities::Entity* ent1);
            void removeEntity(Entities::Entity* ent1);
            
            const CollisionData collisionDetection(Entities::Entity* ent1, Entities::Entity* ent2);
            
            void verifyPlayerEnemy();
            
            void verifyPlayerFloor();
            void verifyEnemyFloor();

            void verifyPlayerObstacle();
            void verifyEnemyObstacle();

            void verifyProjectObstacle();
            void verifyProjectFloor();
            
            void verifyProjectEnemies();
            void verifyProjectPlayers();
            //NEED BETTER POSITION, or player kill himself void verifyProjecPlayers();

            void run();
    };
}

#endif
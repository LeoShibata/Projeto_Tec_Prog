#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "Entities/Entity.hpp"
#include "Entities/Characters/Player.hpp"
#include "Entities/Characters/Enemies/Enemies.hpp"

namespace Entities::Obstacles {
    class Obstacle : public Entity {
        protected:
            bool harmful;
            static Characters::Player* pPlayer1;
            static Characters::Player* pPlayer2;
    
            
        public:
            Obstacle(sf::Vector2f position, sf::Vector2f size, float speed);
            virtual ~Obstacle();

            static void setPlayer1(Characters::Player* pPlayer);
            static void setPlayer2(Characters::Player* pPlayer);
            virtual void collision(Entity* other, float ds, int collisionType);
            
            void update() override;
            
            virtual void execute() = 0;
            virtual void handleCollision(Entities::Characters::Player* pPlayer, float ds, int collisionType) = 0;
            virtual void handleCollision(Entities::Characters::Enemies* pEnemy, float ds, int collisionType) = 0; 
    };
}

#endif
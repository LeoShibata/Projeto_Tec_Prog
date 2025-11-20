#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "Entities/Obstacles/Obstacle.hpp"
#include <iostream>
namespace Entities::Obstacles {
    class Platform : public Obstacle {
        // private:
        //     float friction;


        public:
            Platform(sf::Vector2f position, sf::Vector2f size);
            ~Platform();

            void handleCollision(Entities::Characters::Player* pPlayer, float ds, int collisionType);
            void handleCollision(Entities::Characters::Enemies* pEnemy, float ds, int collisionType);

            void execute() override;    
    };
}

#endif
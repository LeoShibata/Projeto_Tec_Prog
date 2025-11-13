#ifndef SPIKE_HPP
#define SPIKE_HPP

#include "Entities/Obstacles/Obstacle.hpp"

namespace Entities::Obstacles {
    class Spike : public Obstacle {
        // criar atributo específico

        public:
            Spike(sf::Vector2f position, sf::Vector2f size);
            ~Spike();

            void handleCollision(Entities::Characters::Player* pPlayer, float ds, int collisionType);
            void handleCollision(Entities::Characters::Enemies* pEnemy, float ds, int collisionType);
    };
}

#endif
#ifndef SPIKE_HPP
#define SPIKE_HPP

#include "Entities/Obstacles/Obstacle.hpp"

namespace Entities::Obstacles {
    class Spike : public Obstacle {
        // criar atributo específico

        public:
            Spike(sf::Vector2f position, sf::Vector2f size);
            ~Spike();

            void handleCollision(Entities::Characters::Player* pPlayer, sf::Vector2f ds) override;
            void handleCollision(Entities::Characters::Enemies* pEnemy, sf::Vector2f ds) override;
    };
}

#endif
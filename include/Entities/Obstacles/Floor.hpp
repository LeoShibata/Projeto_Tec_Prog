#ifndef FLOOR_HPP
#define FLOOR_HPP

#include "Entities/Obstacles/Obstacle.hpp"

namespace Entities::Obstacles {
    class Floor : public Obstacle {
        private:
            sf::Texture texture;

        public:
            Floor(sf::Vector2f position, sf::Vector2f size);
            ~Floor();

            void handleCollision(Entities::Characters::Player* pPlayer, sf::Vector2f ds) override;
            void handleCollision(Entities::Characters::Enemies* pEnemy, sf::Vector2f ds) override;
    };
}

#endif
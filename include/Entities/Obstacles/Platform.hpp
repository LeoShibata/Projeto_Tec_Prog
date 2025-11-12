#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "Entities/Obstacles/Obstacle.hpp"

namespace Entities::Obstacles {
    class Platform : public Obstacle {
        private:
            int height;

        public:
            Platform(sf::Vector2f position, sf::Vector2f size);
            ~Platform();

            void handleCollision(Entities::Characters::Player* pPlayer, sf::Vector2f ds) override;
            void handleCollision(Entities::Characters::Enemies* pEnemy, sf::Vector2f ds) override;
    };
}

#endif
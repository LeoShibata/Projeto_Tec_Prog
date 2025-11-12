#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "Entities/Entity.hpp"
#include "Entities/Characters/Player.hpp"
#include "Entities/Characters/Enemies/Enemies.hpp"

namespace Entities::Obstacles {
    class Obstacle : public Entity {
        protected:
            bool harmful;

        public:
            Obstacle(sf::Vector2f position, sf::Vector2f size, float speed);
            virtual ~Obstacle();

            void update() override;
            void execute() override;
            virtual void collision(Entity* other, sf::Vector2f ds) override;

            virtual void handleCollision(Entities::Characters::Player* pPlayer, sf::Vector2f ds) = 0;
            virtual void handleCollision(Entities::Characters::Enemies* pEnemy, sf::Vector2f ds) = 0; 
    };
}

#endif
#ifndef SPIKE_HPP
#define SPIKE_HPP

#include "Entities/Obstacles/Obstacle.hpp"

namespace Entities::Obstacles {
    class Spike : public Obstacle {
        private: 
            int damage; // espinhos com dano diferente
           
            Animation::Animator animation;
            sf::Clock clock;

            bool isActive;
            float activationDistanceSq;


        private:
            void initialize();

        public:
            Spike(sf::Vector2f position, sf::Vector2f size);
            ~Spike();

            void handleCollision(Entities::Characters::Player* pPlayer, float ds, int collisionType);
            void handleCollision(Entities::Characters::Enemies* pEnemy, float ds, int collisionType);

            void execute() override;
    };
}

#endif
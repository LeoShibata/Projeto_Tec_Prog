#ifndef SKELETON_HPP 
#define SKELETON_HPP

#include "Entities/Characters/Enemies/Enemies.hpp"
#include "SFML/System/Clock.hpp"

#include <cmath>

namespace Entities::Characters {
    class Skeleton : public Enemies {
        private: 
            float soul; // Mudar atributo
            sf::Clock collisionTimer;
            float collisionCooldown;
            bool isStunned;
        
        private:
            void initialize();

        public:
            Skeleton(const sf::Vector2f position, const sf::Vector2f size, int maldade);
            ~Skeleton();

            void movementPatten(); // Implementar 
            void followPlayer(sf::Vector2f playerPos);
            void updateAnimation();

            void move() override;
            void update() override;
            void execute() override;
            void collision(Entities::Entity* other, sf::Vector2f ds) override;    

    };
}

#endif
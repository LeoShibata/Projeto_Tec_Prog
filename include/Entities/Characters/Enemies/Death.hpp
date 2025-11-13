#ifndef DEATH_HPP 
#define DEATH_HPP

#include "Entities/Characters/Enemies/Enemies.hpp"
#include "SFML/System/Clock.hpp"

#include <cmath>

namespace Entities::Characters {
    class Death : public Enemies {
        private: 
            float soul; // Mudar atributo
            sf::Clock collisionTimer;
            float collisionCooldown;
            bool isStunned;

            static constexpr float DETECTION_RADIUS = 250.f;
            static constexpr float DETECTION_RADIUS_SQ = DETECTION_RADIUS * DETECTION_RADIUS;
        
        private:
            void initialize();

        public:
            Death(const sf::Vector2f position, const sf::Vector2f size, int maldade);
            ~Death();

            void movementPattern(); // Implementar 
            void followPlayer(sf::Vector2f playerPos);
            void updateAnimation();

            void move() override;
            void update() override;
            void execute() override;
            void collision(Entities::Entity* other, sf::Vector2f ds) override;    

    };
}

#endif
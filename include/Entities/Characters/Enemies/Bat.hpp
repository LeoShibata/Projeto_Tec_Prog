#ifndef BAT_HPP
#define BAT_HPP

#include "Entities/Characters/Enemies/Enemies.hpp"
#include "SFML/System/Clock.hpp"

#include <cmath>

namespace Entities::Characters {
    class Bat : public Enemies {
        private:
            float soul;
            sf::Clock collisionTimer;
            float collisionCooldown;
            bool isStunned;

            static constexpr float DETECTION_RADIUS = 250.f;
            static constexpr float DETECTION_RADIUS_SQ = DETECTION_RADIUS * DETECTION_RADIUS;

        private:
            void initialize();
            sf::Vector2f normalize(sf::Vector2f vector);
            
        public:
            Bat(const sf::Vector2f position, const sf::Vector2f size, int maldade);
            ~Bat();
            
            void movementPattern(); // Ainda não implementado
            void followPlayer(sf::Vector2f playerPos);
            void updateAnimation();

            void move() override;
            void update () override;
            void execute() override;
            void collision(Entities::Entity* other, float ds, int collisionType);
    };
}

#endif

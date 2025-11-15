#ifndef DEATH_HPP 
#define DEATH_HPP

#include "Entities/Characters/Enemies/Enemies.hpp"
#include "SFML/System/Clock.hpp"

#include <cmath>

namespace Stages {
    class Stage;
}

namespace Entities::Characters {
    class Death : public Enemies {
        private: 
            float soul; // Mudar atributo

            sf::Clock collisionTimer;
            Stages::Stage* pStage;

            float collisionCooldown;
            bool isStunned;

            static constexpr float DETECTION_RADIUS = 250.f;
            static constexpr float DETECTION_RADIUS_SQ = DETECTION_RADIUS * DETECTION_RADIUS;
        
        private:
            void initialize();
            void attack();
            sf::FloatRect getAttackHitbox() const;

        public:
            Death(const sf::Vector2f position, const sf::Vector2f size, int maldade);
            ~Death();

            void movementPattern(); // Implementar 
            void followPlayer(sf::Vector2f playerPos);
            void updateAnimation();
            void shoot();

            void move() override;
            void update() override;
            void execute() override;
            void setStage(Stages::Stage* pStage);

            void collision(Entities::Entity* other, float ds, int collisionType) override;    

    };
}

#endif
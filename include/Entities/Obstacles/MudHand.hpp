#ifndef MUDHAND_HPP
#define MUDHAND_HPP

#include "Entities/Obstacles/Obstacle.hpp"
#include "Animation/Animator.hpp"
#include "SFML/System/Clock.hpp"

namespace Entities::Obstacles {
    class MudHand : public Obstacle {
        private:
            sf::Clock clock;
            float dt;
            Animation::Animator animation;
            int damageAmount;
            float slowDuration;
            sf::Texture texture;


        private:
            void initialize();

        public:
            MudHand(sf::Vector2f position, sf::Vector2f size);
            ~MudHand();

            void update();

            void handleCollision(Entities::Characters::Player* pPlayer, float ds, int collisionType) override;
            void handleCollision(Entities::Characters::Enemies* pEnemy, float ds, int collisionType) override;
    };
}

#endif
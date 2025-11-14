#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entities/Characters/Character.hpp"

namespace Entities::Characters {
    class Player : public Character {
        private:
            float jump_h; // verificar esse atributo

            sf::Clock attackTimer;
            float attackCooldown;
            float attackDuration;

            sf::Clock damageTimer;
            float damageCooldown;

        private:
            void initialize();

        public:
            Player(const sf::Vector2f position, const sf::Vector2f size);
            virtual ~Player();
            
            void jump();
            void attack();
            bool getIsAttacking() const;
            sf::FloatRect getAttackHitbox() const;
            void updateAnimation();

            void move() override;
            void update() override;
            void execute() override;
            void collision(Entities::Entity* other, float ds, int collisionType);
    };
}

#endif

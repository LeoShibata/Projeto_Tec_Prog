#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entities/Characters/Character.hpp"

namespace Stages{
    class Stage;
} //referencia bidirecional, fazer foward declaration para evitar include circular dependecies;
namespace Entities::Characters {
    class Player : public Character {
        private:
            float jump_h; // verificar esse atributo

            sf::Clock attackTimer;
            float attackCooldown;
            float attackDuration;

            sf::Clock damageTimer;
            float damageCooldown;
            float damageAnimationDuration;
      
            Stages::Stage* pStage;
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

            void shoot();
            void move() override;
            void update() override;
            void execute() override;
            void collision(Entities::Entity* other, float ds, int collisionType);
            void setStage(Stages::Stage* pStage);
    };
}

#endif

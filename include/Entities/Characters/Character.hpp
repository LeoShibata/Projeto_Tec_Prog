#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entities/Entity.hpp"
#include "Animation/Animator.hpp"

namespace Entities::Characters {
    class Character : public Entity {
        public: 
            bool isDying;


        protected:
            int health;
            bool isAlive;
            Animation::Animator animation;
            
            bool canMove;
            bool isMovingLeft;
            bool isMoving;
            
            sf::Clock attackTimer;
            bool isAttacking;
            float attackCooldown;
            float attackDuration;

            sf::Clock damageTimer;
            float damageCooldown;
            float damageAnimationDuration;

            sf::Clock dieTimer;
            float dieAnimationDuration;

        public:
            Character(const sf::Vector2f position, const sf::Vector2f size, const float speed);
            virtual ~Character();

            void adjustPosition(sf::Vector2f ds);
            void startMovingLeft();
            void startMovingRight();
            void stopMoving();
            void setOnGround(bool ground);
            bool getOnGround() const;
            
            int getHealth() const;
            bool getIsAlive() const;
            virtual void takeDamage(int damage);
            
            void execute() override;

            virtual void move() = 0;
            virtual void update() = 0;
    };
}

#endif

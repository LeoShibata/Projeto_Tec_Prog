#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entities/Entity.hpp"
#include "Animation/Animator.hpp"

namespace Entities::Characters {
    class Character : public Entity {
        protected:
            sf::Clock clock;
            float dt;
            bool canMove;
            bool isMovingLeft;
            bool onGround;
            bool isMoving;
            bool isAtacking;
            
            float jumpSpeed;
            Animation::Animator animation;
            static const float GRAVITY;

        public:
            Character(const sf::Vector2f position, const sf::Vector2f size, const float speed);
            virtual ~Character();

            void startMovingLeft();
            void startMovingRight();
            void stopMoving();
            void setOnGround(bool ground);
            bool getOnGround() const;

            virtual void move() = 0;
            virtual void update() = 0;
            
            void execute() override;
    };
}

#endif

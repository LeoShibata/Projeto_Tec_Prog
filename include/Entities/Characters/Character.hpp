#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entities/Entity.hpp"

namespace Entities::Characters {
    class Character : public Entity {
        protected:
            sf::Clock clock;
            float dt;
            bool canMove;
            bool isMovingLeft;

        public:
            Character(const sf::Vector2f position, const sf::Vector2f size, const float speed);
            virtual ~Character();

            void startMovingLeft();
            void startMovingRight();
            void stopMoving();

            virtual void move() = 0;
            virtual void update() = 0;
            
            void execute() override;
    };
}

#endif

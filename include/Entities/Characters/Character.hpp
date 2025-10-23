#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entities/Entity.hpp"

namespace Characters {
    class Character : public Entity {
        protected:
            sf::Vector2f finalVelocity;
            bool canMove;
            bool isMovingLeft;
            sf::Clock clock;
            float dt;

        public:
            Character(const sf::Vector2f position, const sf::Vector2f size, const float speed);
            ~Character();
            void move(const bool isMovingLeft);
            void stop();
            void updatePosition();
            virtual void update() = 0;
            void execute() override;
    };
}

#endif
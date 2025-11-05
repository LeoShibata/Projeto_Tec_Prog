#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entities/Entity.hpp"

namespace Entities::Characters {
    class Character : public Entity {
        protected:
            sf::Vector2f velocity;
            bool canMove;
            bool isMovingLeft;
            sf::Clock clock;
            float dt;

        public:
            Character(const sf::Vector2f position, const sf::Vector2f size, const float speed);
            ~Character();
            virtual void move() = 0;
            virtual void update() = 0;
            void execute() override;
    };
}

#endif

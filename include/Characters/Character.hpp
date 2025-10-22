#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>

namespace Characters {
    class Character {
        protected:
            sf::RectangleShape body;
            sf::Vector2f finalVelocity;
            bool canMove;
            bool isMovingLeft;
            sf::Clock clock;
            float dt;

        public:
            Character(const sf::Vector2f position, const sf::Vector2f size, const float velocity);
            ~Character();
            const sf::RectangleShape& getBody() const;
            void move(const bool isMovingLeft);
            void stop();
            virtual void update() = 0;
            void updatePosition();
    };
}

#endif
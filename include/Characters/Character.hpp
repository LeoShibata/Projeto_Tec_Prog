#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>

namespace Characters {
    class Character {
        protected:
            sf::RectangleShape body;
            sf::Vector2f velocity;

        public:
            Character(const sf::Vector2f position, const sf::Vector2f size);
            virtual ~Character();
            virtual const sf::RectangleShape& getBody() const;
            virtual void move() = 0;;
    };
}

#endif
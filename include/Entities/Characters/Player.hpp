#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entities/Characters/Character.hpp"

#include <iostream>

namespace Characters {
    class Player : public Character {
        private:
            void initialize();

        public:
            Player(float speed, const sf::Vector2f position, const sf::Vector2f size);
            Player();
            ~Player();
            const sf::RectangleShape& getBody() const override;
            void move() override;
	    void execute() override;
    };
}
#endif

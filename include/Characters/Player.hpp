#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Characters/Character.hpp"

#include <iostream>

namespace Characters {
    class Player : public Character {
        private:
            void initialize();

        public:
            Player(const sf::Vector2f position, const sf::Vector2f size);
            // Player();
            ~Player();
            void update() override;
    };
}
#endif
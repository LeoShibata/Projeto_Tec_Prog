#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entities/Characters/Character.hpp"

namespace Characters {
    class Player : public Character {
        private:
            void initialize();

        public:
            Player(const sf::Vector2f position, const sf::Vector2f size);
            ~Player();
            void update() override;
    };
}

#endif
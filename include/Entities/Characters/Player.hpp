#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entities/Characters/Character.hpp"

namespace Entities::Characters {
    class Player : public Character {

        private:
            float jump_h;
        private:
            void initialize();


        public:
            Player(const sf::Vector2f position, const sf::Vector2f size);
            ~Player();
            void update() override;
            void move() override;
            void collision(Entities::Entity* other) override;
            void moveLeft();
            void moveRight();
    };
}

#endif

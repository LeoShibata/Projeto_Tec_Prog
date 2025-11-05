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
            virtual ~Player();

            void move() override;
            void update() override;
            void collision(Entities::Entity* other) override;
            
    };
}

#endif

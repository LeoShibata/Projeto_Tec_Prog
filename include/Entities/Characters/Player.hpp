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
            
            void jump();

            void move() override;
            void updateAnimation();
            void update() override;
            void execute() override;
            void collision(Entities::Entity* other, sf::Vector2f ds = sf::Vector2f(0.f, 0.f)) override;
    };
}

#endif

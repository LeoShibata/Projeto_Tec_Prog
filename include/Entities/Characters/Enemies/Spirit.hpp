#ifndef SPIRIT_HPP
#define SPIRIT_HPP

#include "Entities/Characters/Enemies/Enemies.hpp"

#include <cmath>

namespace Entities::Characters {
    class Spirit : public Enemies {
        private:
            float soul;

        private:
            void initialize();
            sf::Vector2f normalize(sf::Vector2f vector);
            
        public:
            Spirit(const sf::Vector2f position, const sf::Vector2f size, int maldade);
            ~Spirit();
            
            void movementPattern();
            void followPlayer(sf::Vector2f playerPos);
            
            void move() override;
            void update () override;
            void execute() override;
            void collision(Entities::Entity* other, sf::Vector2f ds) override;
    };
}

#endif

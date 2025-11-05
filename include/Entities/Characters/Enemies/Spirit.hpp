#ifndef SPIRIT_HPP
#define SPIRIT_HPP

#include "Entities/Characters/Enemies/Enemy.hpp"

namespace Entities::Characters {
    class Spirit : public Enemy {
        private:
            void initialize();

        public:
            Spirit(const sf::Vector2f position, const sf::Vector2f size);
            virtual ~Spirit();

            void move() override;
            void update() override;
            void collision(Entities::Entity* other, sf::Vector2f ds = sf::Vector2f(0.f, 0.f)) override;
    };
}

#endif

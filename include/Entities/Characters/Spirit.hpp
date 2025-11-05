#ifndef SPIRIT_HPP
#define SPIRIT_HPP

#include "Entities/Characters/Enemies.hpp"

namespace Entities::Characters {
    class Spirit : public Enemies {
        
        private:
            float soul;

        private:
            void initialize();

        public:
            Spirit(const sf::Vector2f position, const sf::Vector2f size, int maldade);
            ~Spirit();
            void collision(Entities::Entity* other) override;
            void movementPattern();
            void followPlayer(sf::Vector2f playerPos);
            void execute() override;
            void update() override;
            void move() override;
    };
}

#endif

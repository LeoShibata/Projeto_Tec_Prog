#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entities/Characters/Character.hpp"

namespace Entities::Characters {
    class Enemies : public Character {
        private:
            void initialize();
            int nivel_maldade;

        public:
            Enemies(const sf::Vector2f position, const sf::Vector2f size, int maldade);
            ~Enemies();
            virtual void update() = 0;
    };
}

#endif

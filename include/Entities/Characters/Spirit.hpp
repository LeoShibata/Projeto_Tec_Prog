#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entities/Characters/Character.hpp"

namespace Entities::Characters {
    class Spirit : public Enemies {
        private:
            void initialize();
            int nivel_maldade;

        public:
            Spirit(const sf::Vector2f position, const sf::Vector2f size);
            ~Spirit();
            void collision(Entities::Entity* other) override;
    };
}

#endif

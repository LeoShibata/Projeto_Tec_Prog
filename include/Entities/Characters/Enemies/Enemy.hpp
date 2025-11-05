#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entities/Characters/Character.hpp"

namespace Entities::Characters {
    class Enemy : public Character {
        protected:
            int nivel_maldade;

        private:
            void initialize();
        
        public:
            Enemy(const sf::Vector2f position, const sf::Vector2f size, int maldade);
            virtual ~Enemy();

            virtual void update() = 0;
    };
}

#endif

#ifndef ENEMIES_HPP
#define ENEMIES_HPP

#include "Entities/Characters/Character.hpp"

namespace Entities::Characters {
    class Player;
    class Enemies : public Character {
        private:
            int nivel_maldade;

        protected:
            static Player* pPlayer;
            
        private:
            void initialize();

        protected:
            void playerCollide(Player* pPlayer);

        public:
            Enemies(const sf::Vector2f position, const sf::Vector2f size, int maldade);
            ~Enemies();

            float distanceSq(const sf::Vector2f& v1, const sf::Vector2f& v2);
            static void setPlayer(Player* p);
            void damaging(Player* pPlayer);
            virtual void checkPlayerAttack();
            
            virtual void move() = 0;
            virtual void update() = 0;
            virtual void execute() = 0;

    };
}

#endif

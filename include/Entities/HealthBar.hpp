#ifndef HEALTHBAR_HPP
#define HEATHBAR_HPP

#include "SFML/Graphics.hpp"
#include "Entities/Characters/Player.hpp"

namespace Entities {
    class HealthBar {
        private:
            sf::RectangleShape backBar; // fundo
            sf::RectangleShape innerBar; // vida
            Characters::Character* pPlayer; // ponteiro para jopgador que a barra observa

            float maxHealth;
            float barMaxWidth; // largura max visual

        
        public:
            HealthBar(sf::Vector2f position, sf::Vector2f size, sf::Color color, Characters::Character* player);
            ~HealthBar();

            void update();
            void draw(sf::RenderWindow* window);
            void setPosition(sf::Vector2f position);
    };
}

#endif
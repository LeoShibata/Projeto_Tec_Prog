#include "Entities/HealthBar.hpp"

namespace Entities {
    
HealthBar::HealthBar(sf::Vector2f position, sf::Vector2f size, sf::Color color, Characters::Character* player) : 
    pPlayer(player),
    barMaxWidth(size.x)
{
    backBar.setPosition(position);
    backBar.setSize(size);
    backBar.setFillColor(sf::Color(50, 50, 50));
    backBar.setOutlineThickness(2.f);
    backBar.setOutlineColor(sf::Color::Black);

    innerBar.setPosition(position);
    innerBar.setSize(size);
    innerBar.setFillColor(color);

    // pega vida max do jogador
    if(pPlayer) {
        maxHealth = (float)pPlayer->getHealth();
    } else {
        maxHealth = 100.f;
    }

}


HealthBar::~HealthBar() {
    pPlayer = nullptr;
}


void HealthBar::update() {
    if(pPlayer) {
        float currentHealth = (float)pPlayer->getHealth();
        if(currentHealth < 0) {
            currentHealth = 0;
        }

        float hpPercent = currentHealth / maxHealth; 

        innerBar.setSize(sf::Vector2f(barMaxWidth * hpPercent, innerBar.getSize().y));
    }
}


void HealthBar::draw(sf::RenderWindow* window) {
    window->draw(backBar);
    window->draw(innerBar);
}


void HealthBar::setPosition(sf::Vector2f position) {
    backBar.setPosition(position);
    innerBar.setPosition(position);
}

}  

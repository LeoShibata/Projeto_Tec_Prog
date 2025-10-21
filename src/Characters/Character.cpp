#include "Characters/Character.hpp"

namespace Characters {

Character::Character(const sf::Vector2f position, const sf::Vector2f size) {
    body.setSize(size);
    body.setPosition(position);
    body.setFillColor(sf::Color::Green);
    velocity = sf::Vector2f(0.f, 0.f);
}

Character::~Character() { }

const sf::RectangleShape& Character::getBody() const {
    return body;
}

}

//------------------------------------------------------------

// void andar(const bool toLeft);
// void stop();
// virtual void updatePosition();
// virtual void update() = 0;
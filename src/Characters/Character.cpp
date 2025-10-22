#include "Characters/Character.hpp"

namespace Characters {

Character::Character(const sf::Vector2f position, const sf::Vector2f size, const float velocity) {
    body.setSize(size);
    body.setPosition(position);
    body.setFillColor(sf::Color::Green);
    finalVelocity = sf::Vector2f(velocity, 0.f);
    canMove = false;
    isMovingLeft = false;
    dt = 0.f;
}

Character::~Character() { }

const sf::RectangleShape& Character::getBody() const {
    return body;
}

void Character::move(const bool isMovingLeft) {
    canMove = true;
    this->isMovingLeft = isMovingLeft;
}

void Character::stop() {
    canMove = false;
}

void Character::updatePosition() {
    dt = clock.getElapsedTime().asSeconds();
    float ds = finalVelocity.x * dt;
    if(isMovingLeft) {
        ds *= -1;
    }
    body.move(ds, 0.f);
}

}
#include "Entities/Characters/Character.hpp"

namespace Entities::Characters {

Character::Character(const sf::Vector2f position, const sf::Vector2f size, const float speed) :
    Entity(speed, position, size),
    finalVelocity(speed, 0.f),
    canMove(false),
    isMovingLeft(false),
    dt(0.f)
{
    setVelocity(sf::Vector2f(0.f, 0.f));
}

Character::~Character() { }

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

void Character::execute() { 
    this->update(); 
}

}
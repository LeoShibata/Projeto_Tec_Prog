#include "Entities/Characters/Character.hpp"

namespace Entities::Characters {

Character::Character(const sf::Vector2f position, const sf::Vector2f size, const float speed) :
    Entity(speed, position, size),
    canMove(false),
    isMovingLeft(false),
    dt(0.f)
{
    setVelocity(sf::Vector2f(0.f, 0.f));
}

Character::~Character() { }

void Character::startMovingLeft() {
    canMove = true;
    isMovingLeft = true;
}

void Character::startMovingRight() {
    canMove = true;
    isMovingLeft = false;
}

void Character::stopMoving() {
    canMove = false;
}

void Character::execute() { 
    this->update(); 
}

}

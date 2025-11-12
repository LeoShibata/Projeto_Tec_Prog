#include "Entities/Characters/Character.hpp"

const float Entities::Characters::Character::GRAVITY = 981.f;

namespace Entities::Characters {

Character::Character(const sf::Vector2f position, const sf::Vector2f size, const float speed) :
    Entity(position, size, speed),
    canMove(false),
    isMovingLeft(false),
    dt(0.f),
    onGround(false),
    jumpSpeed(450.f),
    animation(&body)
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

void Character::setOnGround(bool ground) {
    onGround = ground;
}

bool Character::getOnGround() const {
    return onGround;
}

void Character::execute() { 
    this->update(); 
    this->move();
}

}

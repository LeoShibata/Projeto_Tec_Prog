#include "Entities/Characters/Character.hpp"

#include <iostream>

const float Entities::Characters::Character::GRAVITY = 981.f;

namespace Entities::Characters {

Character::Character(const sf::Vector2f position, const sf::Vector2f size, const float speed) :
    Entity(position, size, speed),
    canMove(false),
    isMovingLeft(false),
    isMoving(false),
    dt(0.f),
    onGround(false),
    jumpSpeed(450.f),
    animation(&body),
    health(1000),
    isAlive(true)
{
    setVelocity(sf::Vector2f(0.f, 0.f));
}

Character::~Character() { }

void Character::adjustPosition(sf::Vector2f ds) {
    body.move(ds);
}

void Character::startMovingLeft() {
    if(!isAlive) {
        return;
    }
    canMove = true;
    isMovingLeft = true;
}

void Character::startMovingRight() {
    if(!isAlive) {
        return;
    }
    canMove = true;
    isMovingLeft = false;
}

void Character::stopMoving() {
    if(!isAlive) {
        return;
    }
    canMove = false;
}

void Character::setOnGround(bool ground) {
    onGround = ground;
}

bool Character::getOnGround() const {
    return onGround;
}

int Character::getHealth() const {
    return health;
}

bool Character::getIsAlive() const {
    return isAlive;
}

void Character::takeDamage(int damage) {
    if(!isAlive) {
        return;
    }

    health -= damage;
    if(health < 0) {
        health = 0;
        isAlive = 0;
        std::cout << "ID " << id << " morreu. Vida: " << health << " Vivo:" << isAlive << std::endl;
    }

    std::cout << "ID " << id << " tomou dano! Vida: " << health << " Vivo:" << isAlive << std::endl;
}

void Character::execute() { 
    this->update(); 
    this->move();
}

}

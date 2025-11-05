#include "Entities/Characters/Character.hpp"

namespace Entities::Characters {

Character::Character(const sf::Vector2f position, const sf::Vector2f size, const float speed) :
    Entity(position, size, speed),
    velocity(speed, 0.f),
    canMove(false),
    isMovingLeft(false),
    dt(0.f)
{
    setVelocity(sf::Vector2f(0.f, 0.f));
}

Character::~Character() { }

void Character::execute() { 
    this->update(); 
}

}

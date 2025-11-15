#include "Entities/Entity.hpp"

namespace Entities {

Entity::Entity(sf::Vector2f position, sf::Vector2f size, float speed) :
    Being(size), 
    speed_mod(speed),
    isAlive(true),
    isEraseble(false)
{
    body.setPosition(position);
    velocity = sf::Vector2f(0.f, 0.f);
}

Entity::~Entity() { }

void Entity::setSpeedmod(float spd) {
    speed_mod = spd;
}

void Entity::setVelocity(sf::Vector2f vel) {
    velocity = vel;
}

float Entity::getSpeedmod() {
    return speed_mod;
}

sf::Vector2f Entity::getVelocity() {
    return velocity;
}

IDs::IDs Entity::getTypeId() const {
    return typeId;
}

bool Entity::getIsAlive() const {
    return isAlive;
}
bool Entity::getIsEraseble() const{
    return isEraseble;
}
}

#include "Entities/Entity.hpp"

namespace Entities {

void Entity::setSpeedmod(float spd) {
    speed_mod = spd;
}

void Entity::setVelocity(sf::Vector2f vel) {
    velocity = vel;
}

Entity::Entity(sf::Vector2f position, sf::Vector2f size, float speed) :
    Being(size), 
    speed_mod(speed)
    {
        body.setPosition(position);
        body.setFillColor(sf::Color::Green);
        velocity = sf::Vector2f(0.f, 0.f);
    }

Entity::~Entity() { }

float Entity::getSpeedmod() {
    return speed_mod;
}

sf::Vector2f Entity::getVelocity() {
    return velocity;
}

}

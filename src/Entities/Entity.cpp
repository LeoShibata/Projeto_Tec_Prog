#include "Entities/Entity.hpp"

const float Entities::Entity::GRAVITY = 981.f;

namespace Entities {


Entity::Entity(sf::Vector2f position, sf::Vector2f size, float speed) :
    Being(size), speed_mod(speed), isAlive(true), 
    onGround(false), dt(0.f)
{
    body.setPosition(position);
    velocity = sf::Vector2f(0.f, 0.f);
}


Entity::~Entity() { }


void Entity::applyGravity() {
    if(!onGround) {
        velocity.y += GRAVITY * dt;
    } else {
        if(velocity.y > 0) {
            velocity.y = 0; // se está no chão, a vel zera (Peso x Normal)
        }
    }
}


void Entity::updateDt() {
    dt = clock.getElapsedTime().asSeconds();
    clock.restart();
    
    // limita dt para não quebrar a física
    if(dt > 0.02f) { 
        dt = 0.1f;
    }
}


void Entity::setSpeedmod(float spd) {
    speed_mod = spd;
}


void Entity::setVelocity(sf::Vector2f vel) {
    velocity = vel;
}


sf::Vector2f Entity::getVelocity() {
    return velocity;
}


float Entity::getSpeedmod() {
    return speed_mod;
}


void Entity::setOnGround(bool ground) {
    this->onGround = ground;
}


bool Entity::getOnGround() const {
    return this->onGround;
}


IDs::IDs Entity::getTypeId() const {
    return typeId;
}


bool Entity::getIsAlive() const {
    return isAlive;
}


}

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
    if(dt > 0.05f) { 
        dt = 0.05f;
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


// ---------------- Métodos de Salvamento ----------------

nlohmann::json Entity::saveEntityState() const {
    nlohmann::json j;   
    j["x"] = body.getPosition().x;
    j["y"] = body.getPosition().y;
    j["vel_x"] = velocity.x;
    j["vel_y"] = velocity.y;
    j["typeId"] = static_cast<int>(typeId);
    return j;
}

void Entity::loadEntityState(const nlohmann::json& j) {
    body.setPosition(j["x"], j["y"]);
    velocity.x = j["vel_x"];
    velocity.y = j["vel_y"];
    // typeId definido no contrutor da classe filha
}

// -------------------------------------------------------


}

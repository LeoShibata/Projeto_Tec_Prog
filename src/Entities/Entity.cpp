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
    if (!onGround) {
        // CONSTANTS
        const float DRAG_COEFFICIENT = 0.98f; 
        const float TERMINAL_VELOCITY = 1000.0f;

        velocity.y += GRAVITY * dt /1.35; //o 1.3 apenas aumenta o pulo

        // aproximação da EDO
        
        velocity.y *= std::pow(DRAG_COEFFICIENT, dt * 60.0f); 

        // Limite da integral
        if (velocity.y > TERMINAL_VELOCITY) {
            velocity.y = TERMINAL_VELOCITY;
        }
    } else {
        if (velocity.y > 0) velocity.y = 0;
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

}

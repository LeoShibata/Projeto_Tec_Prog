#include "Entities/Characters/Enemies/Skeleton.hpp"
#include "Entities/Characters/Player.hpp"

namespace Entities::Characters {

void Skeleton::initialize() { }

Skeleton::Skeleton(const sf::Vector2f position, const sf::Vector2f size, int maldade) : 
    Enemies(position, size, maldade),
    soul(0.7f),
    collisionCooldown(0.3f),
    isStunned(false)
{   
    initialize();
    speed_mod = 0.3f;
    body.setFillColor(sf::Color::Yellow);
    collisionTimer.restart();
}

Skeleton::~Skeleton() { }

void Skeleton::movementPatten() { }

void Skeleton::followPlayer(sf::Vector2f playerPos) { 
    static_cast<void>(playerPos);
}

void Skeleton::move() { 
    dt = clock.getElapsedTime().asSeconds();
    clock.restart();

    if(!onGround) {
        velocity.y += GRAVITY * dt;
    }

    float ds_x = velocity.x * dt;
    float ds_y = velocity.y * dt;

    body.move(ds_x, ds_y);
}

void Skeleton::update() { 
    if(isStunned) {
        if(collisionTimer.getElapsedTime().asSeconds() > collisionCooldown) {
            isStunned = false;
        }
    }

    velocity.x = 0;

    if(onGround) {
        velocity.y = 0;
    }

    if(onGround) {
        onGround = false;
    }
}

void Skeleton::execute() { 
    update();
    move();
}

void Skeleton::collision(Entities::Entity* other, sf::Vector2f ds) {
    switch(other->getTypeId()) {
        case(Entities::IDs::player) : {
            break;
        }
        
        default :
            break;
    }

}

}
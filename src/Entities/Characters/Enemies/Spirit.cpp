#include "Entities/Characters/Enemies/Spirit.hpp"
#include "Entities/Characters/Player.hpp"

#include <iostream>

namespace Entities::Characters {
    
void Spirit::initialize() {
    animation.addAnimation("../assets/BatidleFly.png","FLY",9,0.15f, sf::Vector2f(3,2));
    body.setOrigin(sf::Vector2f(getSize().x/2.5f, getSize().y/2.f));
}

Spirit::Spirit(const sf::Vector2f position, const sf::Vector2f size, int maldade) :    
    Enemies(position, size, maldade),
    soul(0.07f),
    collisionCooldown(0.4f),
    isStunned(false)
{
    initialize();
    speed_mod = 3.f;
    body.setFillColor(sf::Color::Magenta);
    collisionTimer.restart();
}

Spirit::~Spirit() { }


sf::Vector2f Spirit::normalize(sf::Vector2f vec) {
    float magnitude = sqrt(vec.x * vec.x + vec.y * vec.y);
    if(magnitude != 0) {
        return sf::Vector2f(vec.x/magnitude, vec.y/magnitude);
    }
    return vec;
} 

void Spirit::followPlayer(sf::Vector2f playerPos) {
    sf::Vector2f direction = playerPos - body.getPosition();
    direction = normalize(direction);

    float speed = speed_mod * soul;
    velocity.x = direction.x * speed;
    velocity.y = direction.y * speed;
}

void Spirit::move() {
    body.move(velocity);
}

void Spirit::update() {
    if (isStunned) {
        if (collisionTimer.getElapsedTime().asSeconds() > collisionCooldown) {
            isStunned = false;
        }
    }

    if (!isStunned && pPlayer != nullptr) {
        followPlayer(pPlayer->getPos());
    } 

    else if (!isStunned) {
        velocity.x = 0;
        velocity.y = 0;
    }   
}

void Spirit::updateAnimation(){
    animation.update(isMovingLeft, "FLY");
}
void Spirit::execute() {
    update();
    updateAnimation();
    move();
}

void Spirit::collision(Entities::Entity* other, sf::Vector2f ds) {
    switch(other->getTypeId()) {
        case(Entities::IDs::obstacle) : {
            if(!isStunned) {
                isStunned = true;
                collisionTimer.restart();
            }
            break;
        }
        
        default :
            break;
    }
}

}
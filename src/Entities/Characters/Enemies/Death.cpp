#include "Entities/Characters/Enemies/Death.hpp"
#include "Entities/Characters/Player.hpp"

#include <cmath>
#include <cstdlib>

namespace Entities::Characters {

void Death::initialize() { }

Death::Death(const sf::Vector2f position, const sf::Vector2f size, int maldade) : 
    Enemies(position, size, maldade),
    soul(0.7f),
    collisionCooldown(0.3f),
    isStunned(false)
{   
    initialize();
    speed_mod = 100.f;
    body.setFillColor(sf::Color::Red);
    collisionTimer.restart();

    if (rand() % 2 == 0) {
        startMovingLeft(); 
    } else { 
        startMovingRight(); 
    }
}

Death::~Death() { }

void Death::followPlayer(sf::Vector2f playerPos) { 
    static_cast<void>(playerPos);
}

void Death::movementPattern() { 
    if(pPlayer == nullptr || isStunned) {
        velocity.x = 0;
        return;
    }

    if(!onGround) {
        return;
    }

    float distance_to_player_sq = distanceSq(body.getPosition(), pPlayer->getPos());
    float current_speed = 0.f;

    if(distance_to_player_sq < DETECTION_RADIUS_SQ) {
        // modo de perseguição
        current_speed = speed_mod;
        float direction_x = pPlayer->getPos().x - body.getPosition().x;

        if(direction_x > 0) {
            startMovingRight();
        } else if(direction_x < 0) {
            startMovingLeft();
        } else {
            stopMoving();
        }
    } else {
        // modo de patrulha
        current_speed = speed_mod * 0.5f;

        if(!canMove) {
            if(rand() % 2 == 0) {
                startMovingLeft();
            } else {
                startMovingRight();
            }
        }
    }

    if(canMove) {
        velocity.x = isMovingLeft ? -current_speed : current_speed;
    } else {
        velocity.x = 0;
    }

    velocity.y = 0.f;
}

void Death::move() { 
    dt = clock.getElapsedTime().asSeconds();
    clock.restart();

    if(!onGround) {
        velocity.y += GRAVITY * dt;
    }

    float ds_x = velocity.x * dt;
    float ds_y = velocity.y * dt;

    body.move(ds_x, ds_y);
}

void Death::update() { 
    if(isStunned) {
        if(collisionTimer.getElapsedTime().asSeconds() > collisionCooldown) {
            isStunned = false;
        }
    }

    movementPattern();

    if(onGround) {
        onGround = false;
    }
}

void Death::execute() { 
    update();
    checkPlayerAttack();
    move();
}

void Death::collision(Entities::Entity* other, float ds, int collisionType) {
    switch(other->getTypeId()) {
        case(Entities::IDs::obstacle) : {
            break;
        }
        case(Entities::IDs::player) : {
            break;
        }
        
        default :
            break;
    }

}

}
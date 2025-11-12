#include "Entities/Characters/Enemies/Skeleton.hpp"
#include "Entities/Characters/Player.hpp"

#include <cmath>
#include <cstdlib>

namespace Entities::Characters {

void Skeleton::initialize() { }

float Skeleton::distanceSq(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2);
}

Skeleton::Skeleton(const sf::Vector2f position, const sf::Vector2f size, int maldade) : 
    Enemies(position, size, maldade),
    soul(0.7f),
    collisionCooldown(0.3f),
    isStunned(false)
{   
    initialize();
    speed_mod = 100.f;
    body.setFillColor(sf::Color::Yellow);
    collisionTimer.restart();

    if (rand() % 2 == 0) {
        startMovingLeft(); 
    } else { 
        startMovingRight(); 
    }
}

Skeleton::~Skeleton() { }


void Skeleton::followPlayer(sf::Vector2f playerPos) { 
    static_cast<void>(playerPos);
}

void Skeleton::movementPattern() { 
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
            startMovingLeft();
        }
    }

    if(canMove) {
        velocity.x = isMovingLeft ? -current_speed : current_speed;
    } else {
        velocity.x = 0;
    }

    velocity.y = 0.f;
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

    movementPattern();

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
        case(Entities::IDs::platform) : {
            if(ds.x < 0.f && ds.y > ds.x) {
                if(isMovingLeft) {
                    startMovingRight();
                } else {
                    startMovingLeft();
                }
            }
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
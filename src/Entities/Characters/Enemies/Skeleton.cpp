#include "Entities/Characters/Enemies/Skeleton.hpp"
#include "Entities/Characters/Player.hpp"

#include <cmath>
#include <cstdlib>

namespace Entities::Characters {

void Skeleton::initialize() {
    animation.addAnimation("../assets/enemies/Necromancer/Idle/spr_NecromancerIdle_strip50.png", "IDLE", 50, 0.15f, sf::Vector2f(4, 4));
    animation.addAnimation("../assets/enemies/Necromancer/Death/spr_NecromancerDeath_strip52.png", "DIE", 52, 0.05f, sf::Vector2f(4, 4));
    animation.addAnimation("../assets/enemies/Necromancer/GetHit/spr_NecromancerGetHitWithoutEffect_strip9.png", "HURT", 9, 0.05f, sf::Vector2f(4, 4));
    //animation.addAnimation("../assets/enemies/Necromancer/Walk/spr_NecromancerWalk_strip10.png", "WALKING", 10, 0.05f, sf::Vector2f(4, 4));
    body.setOrigin(sf::Vector2f(getSize().x/2.5f, getSize().y/2.f));
}

Skeleton::Skeleton(const sf::Vector2f position, const sf::Vector2f size, int maldade) : 
    Enemies(position, size, maldade),
    soul(0.7f),
    collisionCooldown(0.3f),
    isStunned(false)
{   
    initialize();
    speed_mod = 100.f;
    // body.setFillColor(sf::Color::Yellow);
    collisionTimer.restart();

    damageAnimationDuration = 0.3f; // duração da animação hurt
    dieAnimationDuration = 2.6f; // duração da animação die
    damageTimer.restart();

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
        
        float dead_zone = 1.f; // zona morta para ele não ficar se movendo de um lado para o outro
        if(direction_x > dead_zone) {
            startMovingRight();
        } else if(direction_x < -dead_zone) {
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
    if(isDying) {
        velocity = sf::Vector2f(0.f, 0.f);
        if(dieTimer.getElapsedTime().asSeconds() > dieAnimationDuration) {
            isAlive = false;
        }
        return;
    }

    if(isStunned) {
        if(collisionTimer.getElapsedTime().asSeconds() > collisionCooldown) {
            isStunned = false;
        }
    }

    movementPattern();

    if(onGround) {
        onGround = false;
    }

    if(velocity.x == 0.f && velocity.y == 0.f) {
        isMoving = false;
    } else {
        isMoving = true;
    }
}

void Skeleton::updateAnimation() {
    if(isDying) {
        animation.update(isMovingLeft, "DIE");
    } else if(damageTimer.getElapsedTime().asSeconds() < damageAnimationDuration) {
        animation.update(isMovingLeft, "HURT"); 
    } 
    // else if(isMoving) {
    //     animation.update(isMovingLeft, "WALKING");
    // } 
    else {
        animation.update(isMovingLeft, "IDLE");
    }
}

void Skeleton::execute() { 
    update();
    checkPlayerAttack();
    updateAnimation();
    if(!isDying) {
        move();
    }
}

void Skeleton::collision(Entities::Entity* other, float ds, int collisionType) {
    switch(other->getTypeId()) {
        case(Entities::IDs::obstacle) : {
            // if(!isStunned && ds.x < 0.f && ds.y > ds.x) {
            //     if(isMovingLeft) {
            //         startMovingRight();
            //     } else {
            //         startMovingLeft();
            //     }
                
            //     isStunned = true;
            //     collisionTimer.restart();
            // }
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
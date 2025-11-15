#include "Entities/Characters/Enemies/Skeleton.hpp"
#include "Entities/Characters/Player.hpp"

#include <cmath>
#include <cstdlib>

namespace Entities::Characters {

void Skeleton::initialize() {
    animation.addAnimation("../assets/enemies/Skeleton/Idle.png", "IDLE", 4, 0.15f, sf::Vector2f(5, 5));
    animation.addAnimation("../assets/enemies/Skeleton/Death.png", "DIE", 4, 0.15f, sf::Vector2f(5, 5));
    animation.addAnimation("../assets/enemies/Skeleton/Take Hit.png", "HURT", 4, 0.05f, sf::Vector2f(5, 5));
    animation.addAnimation("../assets/enemies/Skeleton/Walk.png", "WALKING", 4, 0.15f, sf::Vector2f(5, 5));
    animation.addAnimation("../assets/enemies/Skeleton/Attack.png", "ATTACK", 8, 0.05f, sf::Vector2f(5, 5));
    body.setOrigin(sf::Vector2f(getSize().x/2.5f, (getSize().y - 1.5)/2.f));
}

Skeleton::Skeleton(const sf::Vector2f position, const sf::Vector2f size, int maldade) : 
    Enemies(position, size, maldade),
    soul(0.7f),
    collisionCooldown(0.3f),
    isStunned(false)
{   
    initialize();
    speed_mod = 100.f;
    collisionTimer.restart();

    damageAnimationDuration = 0.2f; // duração da animação hurt
    dieAnimationDuration = 0.6f; // duração da animação die
    damageTimer.restart();
    
    isAttacking = false;
    attackCooldown = 2.f; // tempo de espera entre os ataques
    attackDuration = 0.4f;
    attackRangeSq = 60.f * 60.f ; // distancia que começa a atacar
    attackTimer.restart();
    
    hasAppliedDamage = false;

    attackDamageStart = 0.25f;
    attackDamageEnd = 0.4f;
   
    if (rand() % 2 == 0) {
        startMovingLeft(); 
    } else { 
        startMovingRight(); 
    }
}

Skeleton::~Skeleton() { }

void Skeleton::attack() {
    if(!isAlive || isAttacking) {
        return;
    }

    isAttacking = true;
    attackTimer.restart();
    stopMoving();
    hasAppliedDamage = false;
}

sf::FloatRect Skeleton::getAttackHitbox() const {
    sf::Vector2f hitPos = getPos();
    sf::Vector2f hitSize(60.f, 40.f); // tam do hitbox do attack 

    if(isMovingLeft) {
        hitPos.x -= hitSize.x;
    } else {
        hitPos.x += 10.f;
    }
    hitPos.y += 10.f;

    return sf::FloatRect(hitPos.x, hitPos.y, hitSize.x, hitSize.y);
}

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
        if(distance_to_player_sq < attackRangeSq && attackTimer.getElapsedTime().asSeconds() > attackCooldown) {
            attack();
            return;
        }

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

    if(isAttacking) {   
        velocity.x = 0.f;
        float currentTime = attackTimer.getElapsedTime().asSeconds();

        if(currentTime >= attackDuration) {
            isAttacking = false;
        }

        if(pPlayer && pPlayer->getIsAlive()) {
            sf::FloatRect myAttackBox = getAttackHitbox();
            sf::FloatRect playerHitbox =pPlayer->getBody().getGlobalBounds();

            if(currentTime >= attackDamageStart && currentTime <= attackDamageEnd) {
                if(myAttackBox.intersects(playerHitbox) && !hasAppliedDamage) {
                    pPlayer->takeDamage(10);
                    hasAppliedDamage = true;
                }
            }
        }
    } else {
        movementPattern();
    }

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
    } else if(isAttacking) {
        animation.update(isMovingLeft, "ATTACK");
    } else if(isMoving) {
        animation.update(isMovingLeft, "WALKING");
    } else {
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
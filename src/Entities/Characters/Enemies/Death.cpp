#include "Entities/Characters/Enemies/Death.hpp"
#include "Entities/Characters/Player.hpp"
#include "Stages/Stage.hpp"
#include <cmath>
#include <cstdlib>

namespace Entities::Characters {

void Death::initialize(){
    pStage = nullptr;
    animation.addAnimation("../assets/enemies/Death/idle2.png", "IDLE", 8, 0.15f, sf::Vector2f(5, 5), 2, 4);
    animation.addAnimation("../assets/enemies/Death/death.png", "DIE", 18, 0.15f, sf::Vector2f(5, 5), 2, 10);
    animation.addAnimation("../assets/enemies/Death/attacking.png", "ATTACK", 13, 0.1f, sf::Vector2f(5, 5), 3, 6);
    body.setOrigin(sf::Vector2f(getSize().x/2.5f, getSize().y/2.f));
}

Death::Death(const sf::Vector2f position, const sf::Vector2f size, int maldade) : 
    Enemies(position, size, maldade),
    soul(0.7f),
    collisionCooldown(0.3f),
    isStunned(false)
{   
    health = 1000;
    initialize();
    speed_mod = 100.f;
    collisionTimer.restart();

    dieAnimationDuration = 2.7f; // duração da animação die
    damageTimer.restart();

    isAttacking = false;
    attackCooldown = 2.f;
    attackDuration = 1.3f; // olhar anim
    attackRangeSq = 60.f * 60.f;
    attackTimer.restart();

    hasAppliedDamage = false;

    attackDamageStart = 0.5f;
    attackDamageEnd = 1.3;

    if (rand() % 2 == 0) {
        startMovingLeft(); 
    } else { 
        startMovingRight(); 
    }
}

Death::~Death() { }

void Death::attack() {
    if(!isAlive || isAttacking) {
        return;
    }

    isAttacking = true;
    attackTimer.restart();
    stopMoving();
    hasAppliedDamage = false;
}

sf::FloatRect Death::getAttackHitbox() const {
    sf::Vector2f hitPos = getPos();
    sf::Vector2f hitSize(60.f, 40.f); // tam do hitbox do attack 

    if(isMovingLeft) {
        hitPos.x -= 50.f;
    } else {
        hitPos.x += 10.f;
    }
    hitPos.y += 10.f;

    return sf::FloatRect(hitPos.x, hitPos.y, hitSize.x, hitSize.y);
}

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
        if(distance_to_player_sq < attackRangeSq && attackTimer.getElapsedTime().asSeconds() > attackCooldown) {
            attack();
            return;
        }

        current_speed = speed_mod;
        float direction_x = pPlayer->getPos().x - body.getPosition().x;

        float dead_zone = 1.f; // zona morta para ele não ficar se movendo de um lado para o outro
        if(direction_x > dead_zone) {
            shoot();
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

void Death::shoot(){
    float speed =10;
    if(isMovingLeft)
        speed *= -1;
    pStage->createProjectile(sf::Vector2f (10,10), 10, speed, 100, sf::Vector2f(body.getPosition().x, body.getPosition().y), getTypeId());
}

void Death::update() { 
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
                    pPlayer->takeDamage(50);
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

void Death::updateAnimation() {
    if(isDying) {
        animation.update(isMovingLeft, "DIE");
    } else if(isAttacking) {
        animation.update(isMovingLeft, "ATTACK");
    } else {
        animation.update(isMovingLeft, "IDLE");
    }
}

void Death::execute() { 
    update();
    checkPlayerAttack();
    updateAnimation();
    if(!isDying) {
        move();
    }
}
void Death::setStage(Stages::Stage* pStage){
    this->pStage = pStage; //this in bidirecional things
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
#include "Entities/Characters/Enemies/Bat.hpp"
#include "Entities/Characters/Player.hpp"

#include <iostream>

namespace Entities::Characters {
    
void Bat::initialize() {
    animation.addAnimation("../assets/enemies/Bat_without_VFX/Bat-IdleFly.png", "IDLEFLY", 9, 0.15f, sf::Vector2f(3, 2));
    animation.addAnimation("../assets/enemies/Bat_without_VFX/Bat-Hurt.png", "HURT", 5, 0.1f, sf::Vector2f(3, 2));
    animation.addAnimation("../assets/enemies/Bat_without_VFX/Bat-Die.png", "DIE", 12, 0.1f, sf::Vector2f(3, 2));
    animation.addAnimation("../assets/enemies/Bat_with_VFX/Bat-Attack1.png", "ATTACK", 8, 0.1f, sf::Vector2f(3, 2));
    body.setOrigin(sf::Vector2f(getSize().x/2.5f, getSize().y/2.f));
}

Bat::Bat(const sf::Vector2f position, const sf::Vector2f size, int maldade) :    
    Enemies(position, size, maldade),
    soul(0.05f),
    collisionCooldown(0.4f),
    isStunned(false)
{
    initialize();
    speed_mod = 3.f;
    collisionTimer.restart(); 
    damageAnimationDuration = 0.3f; // duração da animação hurt
    dieAnimationDuration = 1.f; // duração da animação die
    damageTimer.restart();

    isAttacking = false;
    attackCooldown = 2.f; // tempo de espera entre os ataques
    attackDuration = 0.8f;
    attackRangeSq = 60.f * 60.f ; // distancia que começa a atacar
    attackTimer.restart();
    
    hasAppliedDamage = false;

    attackDamageStart = 0.6f;
    attackDamageEnd = 0.8f;
}

Bat::~Bat() { }

void Bat::attack() {
    if(!isAlive || isAttacking) {
        return;
    }

    isAttacking = true;
    attackTimer.restart();
    stopMoving();
    hasAppliedDamage = false;
}

sf::FloatRect Bat::getAttackHitbox() const {
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

sf::Vector2f Bat::normalize(sf::Vector2f vec) {
    float magnitude = sqrt(vec.x * vec.x + vec.y * vec.y);
    if(magnitude != 0) {
        return sf::Vector2f(vec.x/magnitude, vec.y/magnitude);
    }
    return vec;
} 

void Bat::followPlayer(sf::Vector2f playerPos) {
    sf::Vector2f direction = playerPos - body.getPosition();
    direction = normalize(direction);

    float speed = speed_mod * soul;
    velocity.x = direction.x * speed;
    velocity.y = direction.y * speed;
}

void Bat::move() {
    body.move(velocity);
}

void Bat::update() {
    if(isDying) {
        velocity = sf::Vector2f(0.f, 0.f);
        if(dieTimer.getElapsedTime().asSeconds() > dieAnimationDuration) {
            isAlive = false;
        }
        return;
    }

    if(isStunned) {
        if (collisionTimer.getElapsedTime().asSeconds() > collisionCooldown) {
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
            sf::FloatRect playerHitbox = pPlayer->getBody().getGlobalBounds();
            
            if(currentTime >= attackDamageStart && currentTime <= attackDamageEnd) {
                if(myAttackBox.intersects(playerHitbox) && !hasAppliedDamage) {
                    pPlayer->takeDamage(10);
                    hasAppliedDamage = true;
                }
            }
        }
    }

    else if(!isStunned && pPlayer != nullptr) {
        float distance_to_player_sq = distanceSq(body.getPosition(), pPlayer->getPos());

        if(distance_to_player_sq <  DETECTION_RADIUS_SQ) {
                if(distance_to_player_sq < attackRangeSq && attackTimer.getElapsedTime().asSeconds() > attackCooldown) {
                    attack();
            } else {
                followPlayer(pPlayer->getPos());
            }
        } else {
            velocity.x = 0;
            velocity.y = 0;
        }
    }
    
    else if(!isStunned) {
        velocity.x = 0;
        velocity.y = 0;
    }   

    if(!isAttacking) {
        if(velocity.x > 0.f) {
            isMovingLeft = true;
        } else {
            isMovingLeft = false;
        }
    }
}

void Bat::updateAnimation() {
    if(isDying) {
        animation.update(isMovingLeft, "DIE");
    } else if(damageTimer.getElapsedTime().asSeconds() < damageAnimationDuration) {
        animation.update(isMovingLeft, "HURT");
    } else if(isAttacking) {
        animation.update(isMovingLeft, "ATTACK");
    } else {
        animation.update(isMovingLeft, "IDLEFLY");
    }
}

void Bat::execute() {
    update();
    checkPlayerAttack();
    updateAnimation();
    if (!isDying) {
        move();
    }
}

void Bat::collision(Entities::Entity* other, float ds, int collisionType) {
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
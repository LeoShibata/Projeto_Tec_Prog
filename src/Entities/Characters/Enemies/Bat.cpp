#include "Entities/Characters/Enemies/Bat.hpp"
#include "Entities/Characters/Player.hpp"

#include <iostream>
#include <cmath>

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
    soul(0.05f)
{
    initialize();
    health = 200;
    speed_mod = 3.f;

    // inicialização de atributos de enemies    
    isStunned = false;
    attackDamage = 10;
    detectionRadiusSq = 250.f * 250.f;
    collisionCooldown = 0.4;
    attackDamageStart = 0.6f;
    attackDamageEnd = 0.8f;

    damageAnimationDuration = 0.3f; // duração da animação hurt
    dieAnimationDuration = 1.f; // duração da animação die
    damageTimer.restart();
    attackTimer.restart();
    
    isAttacking = false;
    attackCooldown = 2.f; // tempo de espera entre os ataques
    attackDuration = 0.8f;
    attackRangeSq = 60.f * 60.f ; // distancia que começa a atacar
    
    hasAppliedDamage = false;
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


void Bat::performMovement(Player* pTarget, float distance_to_player_sq) {
    if(!isStunned && pTarget != nullptr) {
        if(distance_to_player_sq <  detectionRadiusSq) {
                if(distance_to_player_sq < attackRangeSq && attackTimer.getElapsedTime().asSeconds() > attackCooldown) {
                    attack();
            } else {
                sf::Vector2f direction = pTarget->getPos() - body.getPosition();
                direction = normalize(direction);

                float speed = speed_mod * soul;
                velocity.x = direction.x * speed;
                velocity.y = direction.y * speed;
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


void Bat::move() {
    body.move(velocity);
}


void Bat::execute() { 
    update();
    checkPlayerAttack();
    updateAnimation();
    if(!isDying) {
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


// ---------------- Métodos de Salvamento ----------------

nlohmann::json Bat::save() {
    nlohmann::json j = saveCharacterState();
    j["type"] = "bat";
    return j;
}

// -------------------------------------------------------

}
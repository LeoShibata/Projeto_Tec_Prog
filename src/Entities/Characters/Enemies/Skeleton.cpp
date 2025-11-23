#include "Entities/Characters/Enemies/Skeleton.hpp"
#include "Entities/Characters/Player.hpp"

#include <cmath>
#include <cstdlib>

namespace Entities::Characters {

    
void Skeleton::initialize() {
    animation.addAnimation("../assets/enemies/Skeleton/Idle.png", "IDLE", 4, 0.15f, sf::Vector2f(6, 6));
    animation.addAnimation("../assets/enemies/Skeleton/Death.png", "DIE", 4, 0.15f, sf::Vector2f(6, 6));
    animation.addAnimation("../assets/enemies/Skeleton/Take Hit.png", "HURT", 4, 0.05f, sf::Vector2f(6, 6));
    animation.addAnimation("../assets/enemies/Skeleton/Walk.png", "WALKING", 4, 0.15f, sf::Vector2f(6, 6));
    animation.addAnimation("../assets/enemies/Skeleton/Attack.png", "ATTACK", 8, 0.05f, sf::Vector2f(6, 6));
    body.setOrigin(sf::Vector2f(getSize().x/2.5f, (getSize().y - 1.5)/2.f));
}


Skeleton::Skeleton(const sf::Vector2f position, const sf::Vector2f size, int maldade) : 
    Enemies(position, size, maldade)
{   
    initialize();
    health = 500;
    speed_mod = 100.f;
    this->canIncreasedDamage = (rand() % 100) < 30;
    this->hasIncreasedDamage = false;

    // inicialização de atributos de enemies    
    isStunned = false;
    attackDamage = 80;  
    detectionRadiusSq = 250.f * 250.f;
    collisionCooldown = 0.3f;
    attackDamageStart = 0.25f;
    attackDamageEnd = 0.4f;

    damageAnimationDuration = 0.2f; // duração da animação hurt
    dieAnimationDuration = 0.6f; // duração da animação die
    damageTimer.restart();
    attackTimer.restart();
    
    isAttacking = false;
    attackCooldown = 2.f; // tempo de espera entre os ataques
    attackDuration = 0.4f;
    attackRangeSq = 60.f * 60.f ; // distancia que começa a atacar
    
    hasAppliedDamage = false;
   
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


void Skeleton::performMovement(Player* pTarget, float distance_to_player_sq) { 
    if(pTarget == nullptr || isStunned) {
        velocity.x = 0;
        return;
    }

    if(!onGround) {
        return;
    }

    float current_speed = 0.f;

    if(distance_to_player_sq < detectionRadiusSq) { // modo de perseguição        
        if(distance_to_player_sq < attackRangeSq && attackTimer.getElapsedTime().asSeconds() > attackCooldown) {
            attack();
            return;
        }

        current_speed = speed_mod;
        float direction_x = pTarget->getPos().x - body.getPosition().x;

        float dead_zone = 1.f; // zona morta para ele não ficar se movendo de um lado para o outro
        if(direction_x > dead_zone) {
            startMovingRight();
        } else if(direction_x < -dead_zone) {
            startMovingLeft();
        } else {
            stopMoving();
        }
    } else { // modo de patrulha
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
    updateDt();
    applyGravity();
    body.move(velocity * dt);
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

    if(this->canIncreasedDamage && !this->hasIncreasedDamage && this->health <= 200) {
        hasIncreasedDamage = true;
        attackDamage += 50;
        attackCooldown = 1.f;
        body.setFillColor(sf::Color::Red);
    }

    checkPlayerAttack();
    updateAnimation();
    if(!isDying) {
        move();
    }
}


void Skeleton::collision(Entities::Entity* other, float ds, int collisionType) {
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


// ---------------- Métodos de Salvamento ----------------

nlohmann::json Skeleton::save() {
    nlohmann::json j = saveCharacterState();
    j["type"] = "skeleton";
    return j;
}

// -------------------------------------------------------

}
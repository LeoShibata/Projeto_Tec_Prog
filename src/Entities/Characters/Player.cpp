#include "Entities/Characters/Player.hpp"
#include "Stages/Stage.hpp"
#include <iostream>

using namespace std;

namespace Entities::Characters {
    
void Player::initialize() { 
    if(playerID == 1) {
        animation.addAnimation("../assets/player/player1/walking.png", "WALKING", 24, 0.05f, sf::Vector2f(3, 4));
        animation.addAnimation("../assets/player/player1/idle.png", "IDLE", 18, 0.1f, sf::Vector2f(3, 4));
        animation.addAnimation("../assets/player/player1/jump.png", "JUMP", 19, 0.05f, sf::Vector2f(3, 4));
        animation.addAnimation("../assets/player/player1/hurt2.png", "HURT", 7, 0.05f, sf::Vector2f(3, 4));
        animation.addAnimation("../assets/player/player1/attack.png", "ATTACK", 26, 0.05f, sf::Vector2f(3, 4));
        animation.addAnimation("../assets/player/player1/bowAttack.png", "SHOOT", 9, 0.05f, sf::Vector2f(8, 6), 3, 3);
        body.setOrigin(sf::Vector2f(getSize().x/2.5f, (getSize().y + 5)/2.5f));
    } else {
        // body.setFillColor(sf::Color::Red);
        animation.addAnimation("../assets/player/player2/Run.png", "WALKING", 8, 0.15f, sf::Vector2f(7, 5));
        animation.addAnimation("../assets/player/player2/Idle.png", "IDLE", 8, 0.15f, sf::Vector2f(7, 5));
        animation.addAnimation("../assets/player/player2/Jump.png", "JUMP", 2, 0.15f, sf::Vector2f(7, 5));
        animation.addAnimation("../assets/player/player2/Take Hit - white silhouette.png", "HURT", 4, 0.08f, sf::Vector2f(7, 5));
        animation.addAnimation("../assets/player/player2/Attack1.png", "ATTACK", 4, 0.1f, sf::Vector2f(7, 5));
        animation.addAnimation("../assets/player/player2/Death.png", "DEATH", 6, 0.15f, sf::Vector2f(7, 5));
        body.setOrigin(sf::Vector2f(getSize().x/2.5f, (getSize().y + 25)/2.5f));
    }
}


Player::Player(const sf::Vector2f position, const sf::Vector2f size, int playerID) :
    Character(position, size, 100.f), playerID(playerID), jumpSpeed(450.f),
    pStage(nullptr), isShooting(false), shootingCooldown(0.45f),
    isSlowed(false), slowDuration(0.f)  
{    
    initialize();
    typeId = IDs::player;
    health = 600;
    speed_mod = 250.f;
    isTakingDamage = false;

    attackDuration = 0.3f;
    attackCooldown = 0.f;

    damageCooldown = 1.f;
    damageAnimationDuration = 0.2f;
}


Player::~Player() { }


void Player::jump() {
    if(onGround && isAlive) {
        velocity.y = -jumpSpeed;
        onGround = false;
    }
}


void Player::applySlow(float duration) {
    isSlowed = true;
    slowDuration = duration;
    slowTimer.restart();
}


void Player::attack() {
    if(!isAlive) {
        return;
    }

    if(attackTimer.getElapsedTime().asSeconds() > attackCooldown) {
        isAttacking = true;
        attackTimer.restart();
        // animação
    }
}


void Player::shoot() {
    if(playerID != 1) {
        return;
    }

    if(!isAlive) {
        return;
    }
    
    if(shootingTimer.getElapsedTime().asSeconds() > shootingCooldown) {
        float speed = 950;
        shootingTimer.restart();
        
        if(isMovingLeft) {
            speed *= -1;
        }
        pStage->createProjectile(sf::Vector2f(10, 10), 10, speed, 400, body.getPosition(), getTypeId(), true);
        isShooting = true; //for animation
    }
}


bool Player::getIsAttacking() const {
    return isAttacking;
}


sf::FloatRect Player::getAttackHitbox() const { // ajustar todos valores conforme necessário
    sf::Vector2f hitPos = getPos();
    sf::Vector2f hitSize(50.f, 40.f); // tamanho da hitbox

    if(isMovingLeft) {
        hitPos.x -= 50.f;
    } else {
        hitPos.x += 10.f;
    }
    hitPos.y += 10.f;

    return sf::FloatRect(hitPos.x, hitPos.y, hitSize.x, hitSize.y);
}


void Player::updateAnimation() {
    sf::Vector2f defaultOrigin;
    if (playerID == 1) {
        defaultOrigin = sf::Vector2f(getSize().x / 2.5f, (getSize().y + 5) / 2.5f);
    } else {
        defaultOrigin = sf::Vector2f(getSize().x / 2.5f, (getSize().y + 25) / 2.5f);
    }

    if(isDying) {
        body.setOrigin(defaultOrigin);
        //animation.update(isMovingLeft, "DEATH");  
        return;
    } 

    if(!isAlive) {
        return;
    }

    if(isShooting) {
        if(playerID == 1) {
            velocity.x = 0;
            animation.update(isMovingLeft, "SHOOT");
            body.setOrigin(defaultOrigin.x + 3.1f, defaultOrigin.y + 2.9f);
        }
    } else {
        body.setOrigin(defaultOrigin); // volta para a origem 
        if(isTakingDamage) {
            animation.update(isMovingLeft, "HURT");
        } else if(isAttacking) {
            animation.update(isMovingLeft, "ATTACK");  
        } else if(!onGround) {
            animation.update(isMovingLeft, "JUMP");
        } else if(isMoving) {
            animation.update(isMovingLeft, "WALKING");
        } else {
            animation.update(isMovingLeft, "IDLE");
        }
    }
}


void Player::takeDamage(int damage) {
    Character::takeDamage(damage);
    isTakingDamage = true;
}


void Player::move() {
    updateDt();
    applyGravity();
    body.move(velocity * dt);
}


void Player::update() {
    if(isTakingDamage) {
        if(damageTimer.getElapsedTime().asSeconds() > damageAnimationDuration) {
            isTakingDamage = false;
        }
    }

    if(isDying) {
        velocity.x = 0.f;
        if(dieTimer.getElapsedTime().asSeconds() > dieAnimationDuration) {
            isAlive = false;
        }   
        return;
    }

    if(!isAlive) {
        velocity.x = 0.f;
        return;
    }

    if(isSlowed && slowTimer.getElapsedTime().asSeconds() > slowDuration) {
        isSlowed = false;
    }

    if(isAttacking && attackTimer.getElapsedTime().asSeconds() > attackDuration) {
        isAttacking = false;
    }

    if(isShooting && shootingTimer.getElapsedTime().asSeconds() > shootingCooldown) {
        isShooting = false;
    }

    if(canMove && !isAttacking) { // permite movimento se o jogador não estiver atacando 
        float currentSpeed = speed_mod;
        if(isSlowed) {
            currentSpeed *= 0.5f;
        }

        if(isMovingLeft) {
            velocity.x = -currentSpeed;
        } else {
            velocity.x = currentSpeed;
        }
    } else {
        velocity.x = 0.f;
    }

    if(velocity.x == 0.f && velocity.y == 0){
        isMoving = false;
    }else{
        isMoving = true;
    }
}


void Player::execute() {
    update();
    updateAnimation();
    
    if(onGround) {
        onGround = false;
    }
    
    move();
}


void Player::setStage(Stages::Stage* pStage){
    this->pStage = pStage; //this in bidirecional things
}


void Player::collision(Entities::Entity* other, float ds, int collisionType) {
    switch(other->getTypeId()) {
        case(Entities::IDs::enemy) : {
            if (damageTimer.getElapsedTime().asSeconds() >= damageCooldown) {
                takeDamage(1); 
            }
            break;        }
        case(Entities::IDs::floor) : {
            break;
        }
        case(Entities::IDs::platform) : {
            // A lógica de colisão já é tratada pela plataforma (Obstacle::collision -> Platform::handleCollision)
            break;
        }

        default :
            break;
    }
}

}

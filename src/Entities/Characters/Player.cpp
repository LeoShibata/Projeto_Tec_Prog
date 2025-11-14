#include "Entities/Characters/Player.hpp"

#include <iostream>
using namespace std;

namespace Entities::Characters {

void Player::initialize() { 
    animation.addAnimation("../assets/playerAnimation/walking.png", "WALKING", 24, 0.05f, sf::Vector2f(3,3));
    animation.addAnimation("../assets/playerAnimation/idle.png", "STOP", 18, 0.08f, sf::Vector2f(3,3));
    animation.addAnimation("../assets/playerAnimation/jump.png", "JUMP", 19, 0.05f, sf::Vector2f(3,3));
    animation.addAnimation("../assets/playerAnimation/hurt2.png", "DAMAGE", 7, 0.05f, sf::Vector2f(3,3));
    animation.addAnimation("../assets/playerAnimation/attack.png", "ATTACK", 26, 0.05f, sf::Vector2f(3,3));
    body.setOrigin(sf::Vector2f(getSize().x/2.5f, getSize().y/2.5f));

}

Player::Player (const sf::Vector2f position, const sf::Vector2f size) :
    Character(position, size, 100.f),
    attackDuration(0.3f),
    attackCooldown(0.f),
    damageCooldown(1.f),
    damageAnimationDuration(0.2f)
{
        
    initialize();
    typeId = IDs::player;

    health = 1000;
    speed_mod = 250.f;

    damageTimer.restart();
}

Player::~Player() { }

void Player::jump() {
    if(onGround && isAlive) {
        velocity.y = -jumpSpeed;
        onGround = false;
    }
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

bool Player::getIsAttacking() const {
    return isAttacking;
}

sf::FloatRect Player::getAttackHitbox() const { // ajustar todos valores conforme necessário
    sf::Vector2f hitPos = getPos();
    sf::Vector2f hitSize(60.f, 40.f); // tamanho da hitbox

    if(isMovingLeft) {
        hitPos.x -= 50.f;
    } else {
        hitPos.x += 10.f;
    }
    hitPos.y += 10.f;

    return sf::FloatRect(hitPos.x, hitPos.y, hitSize.x, hitSize.y);
}

void Player::updateAnimation(){
    if(!isAlive) {
        return;
    }
    
    if(damageTimer.getElapsedTime().asSeconds() < damageAnimationDuration) {
        animation.update(isMovingLeft, "DAMAGE"); 
    } else if(isAttacking) {
        animation.update(isMovingLeft, "ATTACK");  
    } else if(!onGround) {
        animation.update(isMovingLeft, "JUMP");
    } else if(isMoving) {
        animation.update(isMovingLeft, "WALKING");
    } else {
        animation.update(isMovingLeft, "STOP");
    }
}

void Player::move(){
    dt = clock.getElapsedTime().asSeconds();
    clock.restart();

    if(!onGround) {
        velocity.y += GRAVITY * dt;
    }

    float ds_x = velocity.x * dt;
    float ds_y = velocity.y * dt;
    
    body.move(ds_x, ds_y);
}

void Player::update() {
    if(!isAlive) {
        velocity.x = 0.f;
        return;
    }

    if(isAttacking && attackTimer.getElapsedTime().asSeconds() > attackDuration) {
        isAttacking = false;
    }

    if(canMove && !isAttacking) { // permite movimento se o jogador não estiver atacando 
        if(isMovingLeft) {
            velocity.x = -speed_mod;
        } else {
            velocity.x = speed_mod;
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

void Player::collision(Entities::Entity* other, float ds, int collisionType) {
    switch(other->getTypeId()) {
        case(Entities::IDs::enemy) : {
            // if(damageTimer.getElapsedTime().asSeconds() > damageCooldown) {
            //     takeDamage(1); // jogador toma esse dano ao tocar em inimigo
            //     damageTimer.restart();
            // }
            break;      
        }
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

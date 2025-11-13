#include "Entities/Characters/Player.hpp"

#include <iostream>
using namespace std;

namespace Entities::Characters {

void Player::initialize() { 
    animation.addAnimation("../assets/walking.png","WALKING",24, 0.06f, sf::Vector2f(4,4));
    animation.addAnimation("../assets/player.png", "STOP", 1, 1.f, sf::Vector2f(1.5f,1.5f));
    body.setOrigin(sf::Vector2f(getSize().x/2.5f, getSize().y/2.5f));

}

Player::Player (const sf::Vector2f position, const sf::Vector2f size) :
    Character(position, size, 200.f)
{
        
    initialize();
    typeId = IDs::player;
    speed_mod = 300.f;

}

Player::~Player() { }

void Player::jump() {
    if(onGround) {
        velocity.y = -jumpSpeed;
        onGround = false;
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
    if(canMove) {
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

void Player::updateAnimation(){
    if(isMoving == true && onGround== false)
        animation.update(!(isMovingLeft), "WALKING");
    if(isMoving == false && onGround ==false)
        animation.update(!(isMovingLeft), "STOP");
}

void Player::execute() {
    update();

    if(onGround) {
        onGround = false;
    }
    updateAnimation();
    move();
}

void Player::collision(Entities::Entity* other, sf::Vector2f ds) {
    switch(other->getTypeId()) {
        case(Entities::IDs::enemy) : {
            break;      
        }
        // PLatform::handleCollision já chama pPlayer->setOnGround(true) 
        // Para evitar lógica duplicada, só trata o caso de pousar no chão 
        case(Entities::IDs::floor) : {
            // if(ds.y > 0) {
            //     onGround = true;
            //     velocity.y = 0.f;
            // }
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

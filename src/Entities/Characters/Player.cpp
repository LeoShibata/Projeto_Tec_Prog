#include "Entities/Characters/Player.hpp"

#include <iostream>
using namespace std;

namespace Entities::Characters {

void Player::initialize() { }

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

void Player::adjustPosition(sf::Vector2f ds) {
    body.move(ds);
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
}

void Player::execute() {
    update();
    move();
}

void Player::collision(Entities::Entity* other, sf::Vector2f ds) {
    switch(other->getTypeId()) {
        case(Entities::IDs::enemy) : {
            cout << "Player collided with enemy!" << endl;
            break;      
        }
        case(Entities::IDs::platform) : {
            if(ds.x > ds.y) {

            } else {
                if(velocity.y > 0) {
                    onGround = true;
                }   
            }
            break;
        }
        default:
            break;
    }
}

}

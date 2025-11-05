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
    
}

void Player::move(){
    dt = clock.getElapsedTime().asSeconds();
    if(canMove) {
        float ds = speed_mod * dt;
        if(isMovingLeft) {
            ds *= -1;
        }
        body.move(ds, 0.f);
    }
    clock.restart();
}

void Player::update() { }

void Player::collision(Entities::Entity* other, sf::Vector2f ds) {
    switch(other->getTypeId()) {
        case(Entities::IDs::enemy) :
            cout << "Player collided with enemy!" << endl;
            break;
    }
}

}

#include "Entities/Characters/Player.hpp"
#include <stdio.h>

using namespace std;
namespace Entities::Characters {

Player::Player (const sf::Vector2f position, const sf::Vector2f size) :
    Character(position, size, 200.f)
{
    initialize();
    speed_mod = 10.f;
    cout << "teste" << endl;
}

Player::~Player() { }

void Player::moveLeft(){
    velocity.x = -speed_mod;
        cout << "teste1" << endl;
        move();

}

void Player::moveRight(){
    velocity.x = speed_mod;
        cout << "teste2" << endl;
        move();
}

void Player::move(){
    body.move(velocity);
}

void Player::initialize() { }

void Player::update() {

}

void Player::collision(Entities::Entity* other) {
    if(other->getId() == Entities::IDs::plataform) {
        //
    }
}

}

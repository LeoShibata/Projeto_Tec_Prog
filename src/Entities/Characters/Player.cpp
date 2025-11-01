#include "Entities/Characters/Player.hpp"

namespace Entities::Characters {

Player::Player (const sf::Vector2f position, const sf::Vector2f size) :
    Character(position, size, 200.f)
{
    initialize();
}

Player::~Player() { }

void Player::initialize() { }

void Player::update() {
    if(canMove) {
        updatePosition();
    }
    clock.restart();
}

void Player::collision(Entities::Entity* other) {
    if(other->getId() == Entities::IDs::plataform) {
        //
    }
}

}

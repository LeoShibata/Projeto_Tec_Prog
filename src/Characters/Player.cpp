#include "Characters/Player.hpp"

namespace Characters {

Player::Player (const sf::Vector2f position, const sf::Vector2f size) :
    Character(position, size, 200.f)
{
    initialize();
}

// Player::Player() : 
//      Character(sf::Vector2f(50.f, 50.f), sf::Vector2f(50.f, 50.f), 0.6f) 
// {
//     initialize();
// }

Player::~Player() { }

void Player::initialize() { }

void Player::update() {
    if(canMove) {
        updatePosition();
    }
    clock.restart();
}

}

/*
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
    {
        body.move(-velocity.x, 0.f);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
    {
        body.move(velocity.x, 0.f);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
    {
        body.move(0.f, -velocity.y);
    } 
    
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
    {
        body.move(0.f, velocity.y);
    }
*/
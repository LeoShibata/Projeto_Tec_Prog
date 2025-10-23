#include "Entities/Characters/Player.hpp"

namespace Characters {

Player::Player (float speed, const sf::Vector2f position, const sf::Vector2f size) :
    Character(speed, position, size)
{
    initialize();
}

Player::Player() : 
     Character(1.f, sf::Vector2f(50.f, 50.f), sf::Vector2f(50.f, 50.f)) 
{
    initialize();
}

Player::~Player() { }

void Player::initialize() {
    velocity = sf::Vector2f(0.2f, 0.2f);
}

const sf::RectangleShape& Player::getBody() const {
    return body;
}

void Player::move() {
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
}
void Player::execute(){}
}

#include "Entities/Characters/Enemies/Spirit.hpp"
#include "Entities/Characters/Player.hpp"

namespace Entities::Characters {
    
Spirit::Spirit(const sf::Vector2f position, const sf::Vector2f size, int maldade) :    
    Enemies(position, size, maldade), 
    soul(0.02f)
{
    initialize();
    speed_mod = 3.f;
    body.setFillColor(sf::Color::Red);
}

Spirit::~Spirit() { }

void Spirit::initialize() { }

sf::Vector2f Spirit::normalize(sf::Vector2f vec) {
    float magnitude = sqrt(vec.x * vec.x + vec.y * vec.y);
    if(magnitude != 0) {
        return sf::Vector2f(vec.x/magnitude, vec.y/magnitude);
    }
    return vec;
} 

void Spirit::followPlayer(sf::Vector2f playerPos) {
    sf::Vector2f direction = playerPos - body.getPosition();
    direction = normalize(direction);
    float speed = speed_mod * soul;
    velocity.x = direction.x * speed;
    velocity.y = direction.y * speed;
    // if(playerPos.x > body.getPosition().x) {
    //     velocity.x = speed_mod*soul;
    // } else {
    //     velocity.x = -speed_mod*soul;
    // }
    // if(playerPos.y > body.getPosition().y) {
    //     velocity.y = speed_mod*soul;
    // } else {
    //     velocity.y = -speed_mod*soul;
    // }
}

void Spirit::move() {
    body.move(velocity);
}

void Spirit::update() {
    if(pPlayer != nullptr) {
        followPlayer(pPlayer->getPos());
    } else {    
        velocity.x = 0;
        velocity.y = 0;
    }   
}

void Spirit::execute() {
    update();
    move();
}

void Spirit::collision(Entities::Entity *other, sf::Vector2f ds) { }

}
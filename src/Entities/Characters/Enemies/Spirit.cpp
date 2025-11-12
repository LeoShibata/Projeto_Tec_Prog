#include "Entities/Characters/Enemies/Spirit.hpp"
#include "Entities/Characters/Player.hpp"

namespace Entities::Characters {
    
Spirit::Spirit(const sf::Vector2f position, const sf::Vector2f size, int maldade) :    
    Enemies(position, size, maldade), 
    soul(0.07f)
{
    initialize();
    speed_mod = 3.f;

    // texture = pGraphic->loadFileTexture("../assets/enemy.png");
    body.setFillColor(sf::Color::Magenta);
}

Spirit::~Spirit() { }

void Spirit::initialize() {
    animation.addAnimation("../assets/BatidleFly.png","FLY",9,0.15f, sf::Vector2f(3,2));
    body.setOrigin(sf::Vector2f(getSize().x/2.5f, getSize().y/2.f));
 }

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
}

void Spirit::move() {
    body.move(velocity);
}

void Spirit::update() {
    if(pPlayer != nullptr) {
        followPlayer(pPlayer->getPos());
        if(velocity.x < 0){
            isMovingLeft = false;
        }else{
            isMovingLeft = true;
        }
    } else {    
        velocity.x = 0;
        velocity.y = 0;
    }   
}

void Spirit::updateAnimation(){
    animation.update(isMovingLeft, "FLY");
}
void Spirit::execute() {
    update();
    updateAnimation();
    move();
}

void Spirit::collision(Entities::Entity *other, sf::Vector2f ds) { }

}
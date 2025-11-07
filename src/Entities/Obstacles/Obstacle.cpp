#include "Entities/Obstacles/Obstacle.hpp"
#include "Entities/Characters/Player.hpp"

namespace Entities::Obstacles {

Obstacle::Obstacle(sf::Vector2f position, sf::Vector2f size, float speed) :
    Entity(position, size, speed)
{ 
    setVelocity(sf::Vector2f(0.f, 0.f));
}

Obstacle::~Obstacle() { }

void Obstacle::update() { }

void Obstacle::execute() { 
    update();
}

void Obstacle::collision(Entity* other, sf::Vector2f ds) {
    switch (other->getTypeId()) {
        case(Entities::IDs::player):
            Entities::Characters::Player* pPlayer = static_cast<Entities::Characters::Player*>(other);
            handleCollision(pPlayer, ds);
            break;
        default:
            break;
    }
}

}
#include "Entities/Obstacles/Obstacle.hpp"
#include "Entities/Characters/Player.hpp"

namespace Entities::Obstacles {

Obstacle::Obstacle(sf::Vector2f position, sf::Vector2f size, float speed) :
    Entity(position, size, speed)
{ 
    setVelocity(sf::Vector2f(0.f, 0.f));
    typeId = IDs::obstacle;
}

Obstacle::~Obstacle() { }

void Obstacle::update() { }

void Obstacle::execute() { 
    update();
}

<<<<<<< HEAD
void Obstacle::collision(Entity* other, float ds, int collisionType) {
    switch (other->getTypeId()) {
=======
void Obstacle::collision(Entity* other, sf::Vector2f ds) {
    switch(other->getTypeId()) {
>>>>>>> main
        case(Entities::IDs::player) : {
            Entities::Characters::Player* pPlayer = static_cast<Entities::Characters::Player*>(other);
            handleCollision(pPlayer, ds, collisionType);
            break;
        }
        case(Entities::IDs::enemy) : {
            Entities::Characters::Enemies* pEnemy = static_cast<Entities::Characters::Enemies*>(other);
            handleCollision(pEnemy, ds, collisionType);
            break;
        }

        default:
            break;
    }
}

}
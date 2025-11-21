#include "Entities/Obstacles/Obstacle.hpp"
#include "Entities/Characters/Player.hpp"

namespace Entities::Obstacles {


Characters::Player* Obstacle::pPlayer1 = nullptr;
Characters::Player* Obstacle::pPlayer2 = nullptr;


Obstacle::Obstacle(sf::Vector2f position, sf::Vector2f size, float speed) :
    Entity(position, size, speed)
{ 
    setVelocity(sf::Vector2f(0.f, 0.f));
    typeId = IDs::obstacle;
}


Obstacle::~Obstacle() { }


void Obstacle::update() {
    updateDt();
    applyGravity();
    float ds_x = velocity.x * dt;
    float ds_y = velocity.y * dt; 
    body.move(ds_x, ds_y);
}


void Obstacle::setPlayer1(Characters::Player* pPlayer) {
    pPlayer1 = pPlayer;
}


void Obstacle::setPlayer2(Characters::Player* pPlayer) {
    pPlayer2 = pPlayer;
}


void Obstacle::collision(Entity* other, float ds, int collisionType) {
    switch (other->getTypeId()) {
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
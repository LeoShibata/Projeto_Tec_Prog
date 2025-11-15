#include "Entities/Projectile.hpp"
#include <iostream>
using namespace Entities;
using namespace std;

Projectile::Projectile(sf::Vector2f size, int ddamage, float speed, float maxrange, sf::Vector2f position): 
    Entity(position, size, speed), 
    isEraseble(false), 
    dt(0),damage(ddamage),
    maxrange(maxrange),
    distance(0),
    idEnt(0)
{
    typeId = IDs::projectile;
    initialize();
    body.setFillColor(sf::Color::Cyan);
    velocity.x = speed;
    velocity.y = 0;
}
Projectile::~Projectile(){}

void Projectile::removeProjectile(){
    this->isAlive = false;
    velocity.x = 0;
    //replace for deletion after
}

void Projectile::initialize(){
    //animation
}
void Projectile::damageEnemy(Entities::Characters::Enemies* pEnemy){
    pEnemy->takeDamage(damage);
}
void Projectile::collision(Entity* other, float over, int collisionType){
    //would use switch case to make not damage enemies
    //since it should be a boss thing, to damage player,
    //but we want to make the player shoot also, so, need more work
    switch (other->getTypeId())
    {
    case (Entities::IDs::enemy) :
        damageEnemy(static_cast<Entities::Characters::Enemies*> (other));
        break;
    default:
        break;
    }

    removeProjectile();

}

void Projectile::update(){
    // make a projectile physics
    this->distance = distance + abs(velocity.x);
    if (distance >= maxrange)
    {
        removeProjectile();
    }
    
    body.move(velocity);
    
}
void Projectile::execute(){
    
    update();
    //animation after
}
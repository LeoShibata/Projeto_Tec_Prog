#include "Entities/Projectile.hpp"
#include <iostream>
using namespace Entities;
using namespace std;

Projectile::Projectile(sf::Vector2f size, int ddamage, float speed, float maxrange, sf::Vector2f position, int whoShot): 
    Entity(position, size, speed), 
    isEraseble(false), 
    dt(0),damage(ddamage),
    maxrange(maxrange),
    distance(0),
    whoShot(whoShot)
{
    typeId = IDs::projectile;
    initialize();
    body.setFillColor(sf::Color::Cyan);
    velocity.x = speed;
    velocity.y = 0;
}
Projectile::~Projectile(){}

void Projectile::removeProjectile(){
    isAlive = false;
    
    //replace for deletion after
}

void Projectile::initialize(){
    //animation
}
void Projectile::damageEntity(Entity* other){
    if (whoShot == 1){
        cout<< "plauer atirou" << endl;
    switch (other->getTypeId())
    {
    case IDs::enemy :
        static_cast<Entities::Characters::Enemies*> (other)->takeDamage(damage);
        removeProjectile();
        break;
    case IDs::player :
        break;
    default:
        break;
        removeProjectile();
    }
}else{
    switch (other->getTypeId())
    {
    case IDs::player :
        static_cast<Entities::Characters::Player*> (other)->takeDamage(damage);
        removeProjectile();
        break;
    case IDs::enemy :
        break;
    default:
        removeProjectile();
        break;
    }
}
}
void Projectile::collision(Entity* other, float over, int collisionType){
    //this other is who got shot 
    //since it should be a boss thing, to damage player,
    //but we want to make the player shoot also, so, need more work
    
    
    damageEntity(other);
    cout<<"collided projectil" <<endl;

}

void Projectile::update(){
    distance = velocity.x + distance;
    if (distance > maxrange)
        isAlive == false;
    body.move(velocity);
}
void Projectile::execute(){
    update();
    //animation after
}
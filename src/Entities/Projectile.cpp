#include "Entities/Projectile.hpp"
#include <iostream>

using namespace Entities;
using namespace std;

Projectile::Projectile(sf::Vector2f size, int ddamage, float speed, float maxrange, sf::Vector2f position, int whoShot) : 
    Entity(position, size, speed), 
    isEraseble(false), 
    dt(0), damage(ddamage),
    maxrange(maxrange),
    distance(0),
    whoShot(whoShot)
{
    typeId = IDs::projectile;
    initialize();

    if(whoShot == IDs::player) {
        texture = pGraphic->loadFileTexture("../assets/projectile/arrow.png");
        body.setTexture(&texture);
        body.setFillColor(sf::Color::White);

        if(speed < 0) {
            body.setScale(-1.f, 1.f);
            body.setOrigin(size.x, 0.f);
        }
    } else {
        body.setFillColor(sf::Color::Cyan);
    }

    velocity.x = speed;
    velocity.y = 0;
}


Projectile::~Projectile(){}


void Projectile::removeProjectile(){
    isAlive = false;
    velocity.x = 0;
    
    //replace for deletion after
}


void Projectile::initialize(){
    //animation
}


void Projectile::damageEntity(Entity* other){
    if (whoShot == 1) {
        cout<< "player atirou" << endl;
    
        switch (other->getTypeId())
        {
            case IDs::enemy :
                static_cast<Entities::Characters::Enemies*> (other)->takeDamage(damage);
                removeProjectile();
                break;
            case IDs::player :
                break;
            case IDs::obstacle :
                removeProjectile();
                break;
            default:
                break;
                removeProjectile();
            }
    } else {
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
    distance = abs(velocity.x)+ distance;
    if (distance > maxrange)
        removeProjectile();
    body.move(velocity);
}


void Projectile::execute(){
    update();
    //animation after
}
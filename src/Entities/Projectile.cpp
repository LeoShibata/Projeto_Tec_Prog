#include "Entities/Projectile.hpp"
#include "Entities/Obstacles/Platform.hpp"

#include <iostream>

using namespace std;

namespace Entities {

Projectile::Projectile(sf::Vector2f size, int ddamage, float speed, float maxrange, sf::Vector2f position, int whoShot, bool useGravity) : 
    Entity(position, size, speed), isErasable(false),
    damage(ddamage), maxrange(maxrange), distance(0),
    whoShot(whoShot), useGravity(useGravity)
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


Projectile::~Projectile() { }


void Projectile::removeProjectile() {
    isAlive = false;
    velocity.x = 0;
    
    //replace for deletion after
}


void Projectile::initialize() {
    //animation
}


void Projectile::damageEntity(Entity* other) {
    if (whoShot == 1) {
        // cout<< "player atirou" << endl;
        
        switch (other->getTypeId())
        {
            case IDs::enemy :
                static_cast<Entities::Characters::Enemies*> (other)->takeDamage(damage);
                removeProjectile();
                break;
            case IDs::player :
                break;
            case IDs::obstacle :
            case IDs::floor : 
                removeProjectile();
                break;
            default:
                break;
                removeProjectile();
            }
    } else {
        switch (other->getTypeId()) {
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


void Projectile::collision(Entity* other, float over, int collisionType) {
    //this other is who got shot 
    //since it should be a boss thing, to damage player,
    //but we want to make the player shoot also, so, need more work
    
    
    damageEntity(other);
    cout<<"collided projectil" <<endl;

}


void Projectile::update() {
    updateDt();

    if(this->useGravity) {
        applyGravity();
    }

    float ds_x = velocity.x * dt;
    float ds_y = velocity.y * dt;

    // atualiza dist e verifca range
    distance += std::abs(ds_x);
    if(distance > maxrange) {
        removeProjectile();
    }

    body.move(ds_x, ds_y);

    // distance = abs(velocity.x)+ distance;
    // if (distance > maxrange)
    //     removeProjectile();
    // body.move(velocity);
}


void Projectile::execute() {
    update();
    //animation after
}


// ---------------- Métodos de Salvamento ----------------
nlohmann::json Projectile::save() {
    nlohmann::json j = saveEntityState();
    j["type"] = "projectile";
    return j;
}

} // namespace Entities 

#include "Entities/Floor.hpp"
#include "Entities/Characters/Player.hpp"
#include "Entities/Characters/Enemies/Enemies.hpp"

namespace Entities {

Floor::Floor(sf::Vector2f position, sf::Vector2f size) :
    Entity(position, size, 0.f)
{
    typeId = IDs::floor;
    body.setFillColor(sf::Color::Transparent);
    onGround = true;
}


Floor::~Floor() { }


void Floor::collision(Entity* other, float ds, int collisionType) {
    switch(other->getTypeId()) {
        case IDs::player : {
                Characters::Player* pPlayer = static_cast<Characters::Player*>(other);
                if(collisionType == 1) { // Horizontal
                    pPlayer->adjustPosition(sf::Vector2f(ds, 0.f));
                } else { // Vertical
                    if(ds < 0) { 
                        pPlayer->setOnGround(true);
                    }
                    pPlayer->adjustPosition(sf::Vector2f(0.f, ds));
                    pPlayer->setVelocity(sf::Vector2f(pPlayer->getVelocity().x, 0.f));
                }
            }
            break;

        case IDs::enemy : {
                Characters::Enemies* pEnemy = static_cast<Characters::Enemies*>(other);
                ds *= -1; 
                if(collisionType == 1) {
                    pEnemy->adjustPosition(sf::Vector2f(ds, 0.f));
                } else {
                    if(ds < 0) { 
                        pEnemy->setOnGround(true);
                    }
                    pEnemy->adjustPosition(sf::Vector2f(0.f, ds));
                    pEnemy->setVelocity(sf::Vector2f(pEnemy->getVelocity().x, 0.f));
                }
            }
            break;

        default:
            break;
    }
}


void Floor::update() { 
    updateDt();
    applyGravity();
    body.move(velocity * dt);
}


void Floor::execute() { 
    update(); // objeto estático
}


// ---------------- Métodos de Salvamento ----------------
nlohmann::json Floor::save() {
    nlohmann::json j = saveEntityState();
    j["type"] = "floor";
    return j;
}

}
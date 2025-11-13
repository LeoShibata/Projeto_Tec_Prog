#include "Entities/Obstacles/Spike.hpp"
#include "Entities/Characters/Player.hpp"

namespace Entities::Obstacles {

Spike::Spike(sf::Vector2f position, sf::Vector2f size) :
    Obstacle(position, size, 0.f)
{
    body.setFillColor(sf::Color::White);
    // typeId = IDs::Spike;
}

Spike::~Spike() { }

void Spike::handleCollision(Entities::Characters::Player* pPlayer, float ds, int collisionType) {
    pPlayer->takeDamage(1);

    float push;
    // Colisão horizontal (Parede)
    if(collisionType == 1) {
        // Lógica para descobrir se empurra para esquerda ou direita
        
        pPlayer->adjustPosition(sf::Vector2f(ds, 0.f));
        if(pPlayer->getOnGround()) {
            pPlayer->setVelocity(sf::Vector2f(0.f, 0.f));
        }
    } else {
        // colisão vertical (chão ou teto)
        // pousou no chão
        if(ds < 0) { 
            pPlayer->setOnGround(true);
        }

        pPlayer->adjustPosition(sf::Vector2f(0.f, ds));
        pPlayer->setVelocity(sf::Vector2f(pPlayer->getVelocity().x, 0.f));
    }
}

void Spike::handleCollision(Entities::Characters::Enemies* pEnemy, float ds, int collisionType) {
    pEnemy->takeDamage(1);
    float push;
    if(collisionType == 1) { 
        
        pEnemy->adjustPosition(sf::Vector2f(ds, 0.f));
        // Lógica para deslizar do inimigo: Apenas para a velocidade X, mas deixa a y continuar
        // pEnemy->setVelocity(sf::Vector2f(0.f, pEnemy->getVelocity().y));
        
    } else {
        
        if(ds < 0) { 
            pEnemy->setOnGround(true);
        }
        
        pEnemy->adjustPosition(sf::Vector2f(0.f, ds));
        pEnemy->setVelocity(sf::Vector2f(pEnemy->getVelocity().x, 0.f));
    }
}

}
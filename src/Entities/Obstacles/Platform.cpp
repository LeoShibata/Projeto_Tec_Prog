#include "Entities/Obstacles/Platform.hpp"
#include "Entities/Characters/Player.hpp"
using namespace std;
namespace Entities::Obstacles {

Platform::Platform(sf::Vector2f position, sf::Vector2f size) :
    Obstacle(position, size, 0.f)
{
    texture = pGraphic->loadFileTexture("../assets/barrel.png");
    body.setTexture(&texture);
}

Platform::~Platform() { }

void Platform::handleCollision(Entities::Characters::Player* pPlayer, float ds, int collisionType) {
    // Colisão horizontal (Parede)
    if(collisionType == 1) {
        // Lógica para descobrir se empurra para esquerda ou direita
        pPlayer->adjustPosition(sf::Vector2f(ds, 0.f));
        pPlayer->setVelocity(sf::Vector2f(0.f, pPlayer->getVelocity().y));
        cout <<ds << " colisao  obstaculo horizontal" <<endl;

        if(pPlayer->getOnGround()) {
            pPlayer->setVelocity(sf::Vector2f(0.f, 0.f));
        }
    } else {

        // pousou no chão
        if(ds < 0) { 
            pPlayer->setOnGround(true);
        }
        cout <<ds << " colisao  obstaculo vertical" <<endl;
        pPlayer->adjustPosition(sf::Vector2f(0.f, ds));
        pPlayer->setVelocity(sf::Vector2f(pPlayer->getVelocity().x, 0.f));
    }
}

void Platform::handleCollision(Entities::Characters::Enemies* pEnemy, float ds, int collisionType) {
        ds *= -1;
    if(collisionType == 1) { 
        
        pEnemy->adjustPosition(sf::Vector2f(ds, 0.f));
        // Lógica para deslizar do inimigo: Apenas para a velocidade X, mas deixa a y continuar
        pEnemy->setVelocity(sf::Vector2f(0.f, pEnemy->getVelocity().y));
        
    } else {
        if(ds < 0){
            pEnemy->setOnGround(true);
        }

        pEnemy->adjustPosition(sf::Vector2f(0.f, ds));
        pEnemy->setVelocity(sf::Vector2f(pEnemy->getVelocity().x, 0.f));
        
    }

    }
}
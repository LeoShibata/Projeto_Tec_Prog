#include "Entities/Obstacles/Platform.hpp"
#include "Entities/Characters/Player.hpp"

namespace Entities::Obstacles {

Platform::Platform(sf::Vector2f position, sf::Vector2f size) :
    Obstacle(position, size, 0.f)
{
    texture = pGraphic->loadFileTexture("../assets/barrel.png");
    body.setTexture(&texture);
}

Platform::~Platform() { }

void Platform::handleCollision(Entities::Characters::Player* pPlayer, sf::Vector2f ds) {
    float push;
    // Colisão horizontal (Parede)
    if(ds.x > ds.y) {
        // Lógica para descobrir se empurra para esquerda ou direita
        if((pPlayer->getPos().x - getPos().x) > 0) {
            push = -ds.x;
        } else {
            push = ds.x;            
        }
        pPlayer->adjustPosition(sf::Vector2f(push, 0.f));
        if(pPlayer->getOnGround()) {
            pPlayer->setVelocity(sf::Vector2f(0.f, 0.f));
        }
    } else {
        // colisão vertical (chão ou teto)
        if((pPlayer->getPos().y - getPos().y) > 0) {
            push = -ds.y;
        } else {
            push = ds.y;
        }

        // pousou no chão
        if(push < 0) { 
                pPlayer->setOnGround(true);
        }

        pPlayer->adjustPosition(sf::Vector2f(0.f, push));
        pPlayer->setVelocity(sf::Vector2f(pPlayer->getVelocity().x, 0.f));
    }
}

}
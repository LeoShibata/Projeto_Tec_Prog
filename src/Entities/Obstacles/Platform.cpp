#include "Entities/Obstacles/Platform.hpp"

namespace Entities::Obstacles {

Platform::Platform(sf::Vector2f position, sf::Vector2f size) :
    Obstacle(position, size, 0.f)
{
    body.setFillColor(sf::Color::Blue);
}

Platform::~Platform() { }

void Platform::handleCollision(Entities::Characters::Player* pPlayer, sf::Vector2f ds) {
    float push;
    // Colisão horizontal (Parede)
    if(ds.x > ds.y) {
        // Lógica para descobrir se empurra para esquerd aou direita
        if((pPlayer->getPos().x - getPos().x) > 0) {
            push = -ds.x;
            cout << "ta na esquerda" << endl;
        } else {
            push = ds.x;
            cout << "ta na direita" << endl;
            
        }
        pPlayer->adjustPosition(sf::Vector2f(push, 0.f));
        pPlayer->setVelocity(sf::Vector2f(0.f, pPlayer->getVelocity().y));
    } else {
        // colisão vertical (chão ou teto)
        if((pPlayer->getPos().y - getPos().y) > 0) {
            push = -ds.y;
            cout << "ta no teto" << endl;
        } else {
            push = ds.y;
            cout << "ta no chao" << endl;
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
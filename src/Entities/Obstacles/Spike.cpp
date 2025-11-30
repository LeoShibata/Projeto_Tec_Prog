#include "Entities/Obstacles/Spike.hpp"
#include "Entities/Characters/Player.hpp"

namespace Entities::Obstacles {


void Spike::initialize() {
    animation.addAnimation("../assets/obstacles/spikes/hidden.png", "HIDDEN", 1, 0.5f, sf::Vector2f(1, 1), 1, 4);
    animation.addAnimation("../assets/obstacles/spikes/active.png", "ACTIVE", 1, 0.5f, sf::Vector2f(1, 1), 1, 4);
    body.setOrigin(sf::Vector2f(getSize().x/2.f, (getSize().y - 32)/2.f));
}


Spike::Spike(sf::Vector2f position, sf::Vector2f size) :
    Obstacle(position, size, 0.f),
    damage(1), // dano padrão
    animation(&body),
    isActive(false),
    activationDistanceSq(100.f * 100.f)
{
    // typeId = IDs::Spike;
    initialize();
    clock.restart();
    damage = (rand() % 5) + 1; // dano aleatório
    // texture = pGraphic->loadFileTexture("../assets/obstacles/spikes/spikes.png");
    // body.setTexture(&texture);
    // body.setFillColor(sf::Color::White);
}


Spike::~Spike() { }


void Spike::handleCollision(Entities::Characters::Player* pPlayer, float ds, int collisionType) {
    if(!isActive) {
        return;
    }
    
    pPlayer->takeDamage(damage);

    // Colisão horizontal (Parede)
    if(collisionType == 1) {
        // Lógica para descobrir se empurra para esquerda ou direita
        
        pPlayer->adjustPosition(sf::Vector2f(ds, 0.f));
        pPlayer->setVelocity(sf::Vector2f(0.f, pPlayer->getVelocity().y));
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
    if(!isActive) {
        return;
    }
    
    pEnemy->takeDamage(damage);
    ds *= -1;
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


void Spike::execute() {
    bool playerNear = false;

    if(pPlayer1 && pPlayer1->getIsAlive()) {
        sf::Vector2f pPos = pPlayer1->getPos();
        sf::Vector2f myPos = body.getPosition();
        float distSq = (pPos.x - myPos.x)*(pPos.x - myPos.x) + (pPos.y - myPos.y)*(pPos.y - myPos.y);
        if(distSq < activationDistanceSq) {
            playerNear = true;
        }
    }

    if(!playerNear && pPlayer2 && pPlayer2->getIsAlive()) {
        sf::Vector2f pPos = pPlayer2->getPos();
        sf::Vector2f myPos = body.getPosition();
        float distSq = (pPos.x - myPos.x)*(pPos.x - myPos.x) + (pPos.y - myPos.y)*(pPos.y - myPos.y);
        if(distSq < activationDistanceSq) {
            playerNear = true;
        }
    }

    isActive = playerNear;

    if(isActive) {
        animation.update(false, "ACTIVE");
    } else {
        animation.update(false, "HIDDEN");
    }
}


// ---------------- Métodos de Salvamento ----------------
nlohmann::json Spike::save() {
    nlohmann::json j = saveEntityState();
    j["type"] = "spike";
    return j;
}

}
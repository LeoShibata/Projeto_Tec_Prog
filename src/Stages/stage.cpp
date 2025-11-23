#include "Stages/Stage.hpp"
#include "Entities/Characters/Player.hpp"
#include "Managers/StateManager.hpp"

#include <iostream>

using json = nlohmann::json;
using namespace std;

namespace Stages {

Stage::Stage() : 
    Being(sf::Vector2f(0,0)),
    pEvent(Managers::EventManager::getEventManager()),
    pGraphic(Managers::GraphicManager::getGraphicManager()),
    pCollision(nullptr), pPlayer1(nullptr), pPlayer2(nullptr),
    characterList(new List::EntityList()),
    obstacleList(new List::EntityList()),
    structureList(new List::EntityList()),
    projectileList(new List::EntityList()),
    hpBar1(nullptr), hpBar2(nullptr),
    max_bats(20), max_obstacles(12), 
    gameOver(false)
{ 
    pCollision = new Managers::CollisionManager();
    Entities::Characters::Enemies::clearPlayers(); // limpa jogadores estáticos de enemies
}


Stage::~Stage() {
    if(pCollision) {
        delete pCollision;
        pCollision = nullptr;
    }
    if(characterList) {
        delete characterList;
        characterList = nullptr;
    }
    if(obstacleList) {
        delete obstacleList;
        obstacleList = nullptr;
    }
    if(hpBar1) {
        delete hpBar1;
    }
    if(hpBar2) {
        delete hpBar2;
    }
}


// ----------------- Players -----------------
void Stage::createPlayer1(sf::Vector2f pos) {
    pPlayer1 = new Entities::Characters::Player(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize), 1);
    pPlayer1->setStage(static_cast<Stage*>(this));// please work
    characterList->addEntity(pPlayer1);

    pCollision->setPlayer1(pPlayer1);
    pEvent->setPlayer1(pPlayer1);
    Entities::Characters::Enemies::setPlayer1(pPlayer1);
    Entities::Obstacles::Obstacle::setPlayer1(pPlayer1);
    pGraphic->setPlayer1(pPlayer1);

    hpBar1 = new Entities::HealthBar(sf::Vector2f(20.f, 20.f), sf::Vector2f(200.f, 20.f), sf::Color::Red, pPlayer1);
}


void Stage::createPlayer2(sf::Vector2f pos) {
    pPlayer2 = new Entities::Characters::Player(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize), 2);
    pPlayer2->setStage(static_cast<Stage*>(this));// please work
    characterList->addEntity(pPlayer2);

    pCollision->setPlayer2(pPlayer2);
    pEvent->setPlayer2(pPlayer2);
    Entities::Characters::Enemies::setPlayer2(pPlayer2);
    Entities::Obstacles::Obstacle::setPlayer2(pPlayer2);
    pGraphic->setPlayer2(pPlayer2);

    hpBar2 = new Entities::HealthBar(sf::Vector2f(1060.f, 20.f), sf::Vector2f(200.f, 20.f), sf::Color::Blue, pPlayer2);
}


// ----------------- Obstacles -----------------
void Stage::createFloor(sf::Vector2f pos) {
    Entities::Floor* pFloor = new Entities::Floor(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize));
    structureList->addEntity(pFloor);
    pCollision->includeEntity(static_cast<Entities::Entity*>(pFloor));
}


void Stage::createPlatform(sf::Vector2f pos) {
    Entities::Obstacles::Platform* pPlat = new Entities::Obstacles::Platform(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize));
    obstacleList->addEntity(pPlat);
    pCollision->includeEntity(static_cast<Entities::Entity*>(pPlat));
}


// ----------------- Projectile -----------------
void Stage::createProjectile(sf::Vector2f size, int ddamage, float speed, float maxrange, sf::Vector2f position, int whoShot, bool useGravity){
    Entities::Projectile* pProjectile = new Entities::Projectile(size, ddamage, speed, maxrange, position, whoShot, useGravity);
    characterList->addEntity(pProjectile);
    pCollision->includeEntity(pProjectile);
}


// ----------------- Enemies -----------------
void Stage::createSkeleton(sf::Vector2f pos) {
    Entities::Characters::Skeleton* pSkeleton = new Entities::Characters::Skeleton(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize), 10);
    characterList->addEntity(pSkeleton);
    pCollision->includeEntity(pSkeleton);
}


void Stage::draw(sf::RenderWindow* window) {
    sf::View currentView = window->getView();

    background2.setPosition(
        currentView.getCenter().x - currentView.getSize().x / 2,
        currentView.getCenter().y - currentView.getSize().y / 2
    );
    background3.setPosition(
        currentView.getCenter().x - currentView.getSize().x / 2,
        currentView.getCenter().y - currentView.getSize().y / 2
    );

    window->draw(background2);
    window->draw(background3);
    window->draw(background);
    characterList->drawAll(window);
    obstacleList->drawAll(window);
    structureList->drawAll(window);

    // desenha a barra de vida
    window->setView(window->getDefaultView());
    if(hpBar1 && pPlayer1 && pPlayer1->getIsAlive()) {
        hpBar1->draw(window);
    }
    if(hpBar2 && pPlayer2 && pPlayer2->getIsAlive()) {
        hpBar2->draw(window);
    }

    window->setView(currentView); // restaura a view do jogo
}


void Stage::execute() {
    // cout << "called the stage execute" << endl;
    
    List::EntityList* chars = characterList;
    for(int i = 0; i < chars->getSize(); i++) {
        if((*chars)[i]->getIsAlive()) {
           (*chars)[i]->execute(); 
        }
    }

    structureList->executeAll();
    obstacleList->executeAll();

    if(hpBar1) {
        hpBar1->update();
    }
    if(hpBar2) {
        hpBar2->update();
    }

    for(int i = chars->getSize() - 1; i  >= 0; i--) {
        Entities::Entity* ent = (*chars)[i];

        if(!ent->getIsAlive()) {
            if(ent->getTypeId() == Entities::IDs::player) {
                // para tela de gameover
                // Managers::StateManager::getStateManager()->addState(6);
                // para dois jogadores não funciona
            } else {
                pCollision->removeEntity(ent);
                chars->removeEntity(i);
                delete ent;
                ent = nullptr;
            }
            
        }

    }

    pCollision->run();

    bool p1Dead = (pPlayer1 && !pPlayer1->getIsAlive());
    bool p2Dead = (pPlayer2 && !pPlayer2->getIsAlive());
    bool p2Exists = (pPlayer2 != nullptr);

    if(!gameOver && p1Dead && (!p2Exists || p2Dead)) {
        gameOver = true;
        Managers::StateManager::getStateManager()->addState(6);
    }
}

}
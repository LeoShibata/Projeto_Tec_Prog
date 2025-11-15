#include "Stages/stage.hpp"
#include "Entities/Characters/Player.hpp"

using json = nlohmann::json;
using namespace std;

namespace Stages {

Stage::Stage() : 
    Being(sf::Vector2f(0,0)),
    pEvent(Managers::EventManager::getEventManager()),
    pGraphic(Managers::GraphicManager::getGraphicManager()),
    pCollision(nullptr),
    characterList(new List::EntityList()),
    obstacleList(new List::EntityList()),
    projectileList(new List::EntityList()),
    max_bats(20),
    max_obstacles(12)
{ 
    pCollision = new Managers::CollisionManager();
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
}

// ----------------- Players -----------------
void Stage::createPlayer(sf::Vector2f pos) {
    Entities::Characters::Player* pPlayer = new Entities::Characters::Player(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize));
    pPlayer->setStage(static_cast<Stage*>(this));// please work
    characterList->addEntity(pPlayer);

    pCollision->includeEntity(static_cast<Entities::Entity*>(pPlayer));
    pCollision->setPlayer(pPlayer);

    pEvent->setPlayer(pPlayer);
    Entities::Characters::Enemies::setPlayer(pPlayer);
    pGraphic->setPlayer(pPlayer);
}

// ----------------- Obstacles -----------------
void Stage::createFloor(sf::Vector2f pos) {
    Entities::Obstacles::Floor* pFloor = new Entities::Obstacles::Floor(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize));
    obstacleList->addEntity(pFloor);
    pCollision->includeEntity(static_cast<Entities::Entity*>(pFloor));
}

void Stage::createPlatform(sf::Vector2f pos) {
    Entities::Obstacles::Platform* pPlat = new Entities::Obstacles::Platform(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize));
    obstacleList->addEntity(pPlat);
    pCollision->includeEntity(static_cast<Entities::Entity*>(pPlat));
}

void Stage::createSpike(sf::Vector2f pos) {
    Entities::Obstacles::Spike* pSpike = new Entities::Obstacles::Spike(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize));
    obstacleList->addEntity(pSpike);
    pCollision->includeEntity(static_cast<Entities::Entity*>(pSpike));
}
// ----------------- Projectile -----------------

void Stage::createProjectile(sf::Vector2f size, int ddamage, float speed, float maxrange, sf::Vector2f position, int whoShot){
    Entities::Projectile* pProjectile = new Entities::Projectile(size, ddamage, speed, maxrange, position, whoShot);
    characterList->addEntity(pProjectile);
    pCollision->includeEntity(pProjectile);

}

// ----------------- Enemies -----------------
void Stage::createBat(sf::Vector2f pos) {
    Entities::Characters::Bat* pBat = new Entities::Characters::Bat(sf::Vector2f(pos),sf::Vector2f(tileSize, tileSize), 10);
    characterList->addEntity(pBat);
    pCollision->includeEntity(pBat);
}

void Stage::createSkeleton(sf::Vector2f pos) {
    Entities::Characters::Skeleton* pSkeleton = new Entities::Characters::Skeleton(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize), 10);
    characterList->addEntity(pSkeleton);
    pCollision->includeEntity(pSkeleton);
}

void Stage::createDeath(sf::Vector2f pos) {
    Entities::Characters::Death* pDeath = new Entities::Characters::Death(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize), 10);
    pDeath->setStage(static_cast<Stage*>(this));
    characterList->addEntity(pDeath);
    pCollision->includeEntity(pDeath);
}


void Stage::draw(sf::RenderWindow* window) {
    window->draw(background);
    characterList->drawAll(window);
    obstacleList->drawAll(window);
}

void Stage::execute() {
    List::EntityList* chars = characterList;
    
    for(int i = 0; i < chars->getSize(); i++) {
        if((*chars)[i]->getIsAlive()) {
           (*chars)[i]->execute(); 
            cout << (*chars)[i]->getTypeId()<< endl;

        }
    }

    obstacleList->executeAll();

    for(int i = chars->getSize() - 1; i  >= 0; i--) {
        Entities::Entity* ent = (*chars)[i];

        if(!ent->getIsAlive()) {
            if(ent->getTypeId() == Entities::IDs::player) {
                // adicionar tela de game over
            } else {
                pCollision->removeEntity(ent);
                chars->removeEntity(i);
                delete ent;
                ent = nullptr;
            }
        }
        
    }

    pCollision->run();
}

}
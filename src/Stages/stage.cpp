#include "Stages/stage.hpp"

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
    max_spirits(20),
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

void Stage::createPlayer(sf::Vector2f pos) {
    Entities::Characters::Player* pPlayer = new Entities::Characters::Player(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize));
    characterList->addEntity(pPlayer);

    pCollision->includeEntity(static_cast<Entities::Entity*>(pPlayer));
    pCollision->setPlayer(pPlayer);

    pEvent->setPlayer(pPlayer);
    Entities::Characters::Enemies::setPlayer(pPlayer);
    pGraphic->setPlayer(pPlayer);
}

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

void Stage::draw(sf::RenderWindow* window) {
    window->draw(background);
    
    characterList->drawAll(window);
    obstacleList->drawAll(window);
}

void Stage::execute() {
    characterList->executeAll();
    obstacleList->executeAll();
    pCollision->run();
}

}
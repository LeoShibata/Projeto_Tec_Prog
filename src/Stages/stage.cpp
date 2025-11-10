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
    obstacleList(new List::EntityList())
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

void Stage::draw(sf::RenderWindow* window) {
    characterList->drawAll(window);
    obstacleList->drawAll(window);
}

void Stage::execute() {
    characterList->executeAll();
    obstacleList->executeAll();
    pCollision->run();
}

}
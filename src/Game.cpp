#include "Game.hpp"
#include "Entities/Characters/Player.hpp"
#include "Entities/Characters/Spirit.hpp"

Game::Game() : 
    pGraphic(Managers::GraphicManager::getGraphicManager()),
    pEvent(Managers::EventManager::getEventManager()),
    pCollision(nullptr),
    characterList(nullptr), 
    obstacleList(nullptr)
{   
    if(pGraphic == nullptr) {
        std::cout << "ERROR: Failed to create graphic manager." << std::endl;
        exit(1);
    }

    characterList = new List::EntityList();
    obstacleList = new List::EntityList();

    pCollision = new Managers::CollisionManager(characterList, obstacleList);
    int maldade =10;
    Entities::Characters::Player* player = new Entities::Characters::Player(sf::Vector2f(100.f, 200.f), sf::Vector2f(50.f, 50.f));
    Entities::Characters::Spirit* spirit = new Entities::Characters::Spirit(sf::Vector2f(0.f, 0.f), sf::Vector2f(30.f, 30.f), maldade);
    characterList->addEntity(player);
    characterList->addEntity(spirit);    
    pEvent->setPlayer(player);
    pEvent->setSpirit(spirit);
}   

Game::~Game() {
    if(pCollision) {
        delete pCollision;
        pCollision = nullptr;
    }

    if(characterList) {
        int size = characterList->getSize();
        for(int i = 0; i < size; i++) {
            Entities::Entity* ent = (*characterList)[i];
            if(ent)    
                delete ent;
        }
        delete characterList;   
        characterList = nullptr;
    }

    if(obstacleList) {
        int size = obstacleList->getSize();
        for(int i = 0; i < size; i++) {
            Entities::Entity* ent = (*obstacleList)[i];
            if(ent)
                delete ent;
        }
        delete obstacleList;
        obstacleList = nullptr;
    }
}

void Game::run() {
    while (pGraphic->isWindowOpen())
    {
        pEvent->run();
        pCollision->run();
        pGraphic->clearWindow(); 
        characterList->run(pGraphic->getWindow());
        obstacleList->run(pGraphic->getWindow());
        pGraphic->showElements(); 
    }
}   

#include "Game.hpp"
#include "Entities/Characters/Player.hpp"
#include "Entities/Characters/Enemies/Spirit.hpp"
#include "Entities/Obstacles/Platform.hpp"

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

    pCollision = new Managers::CollisionManager();

    int maldade =10;

    Entities::Characters::Player* player = new Entities::Characters::Player(sf::Vector2f(100.f, 200.f), sf::Vector2f(50.f, 50.f));
    Entities::Characters::Spirit* spirit = new Entities::Characters::Spirit(sf::Vector2f(0.f, 0.f), sf::Vector2f(30.f, 30.f), maldade);
    
    characterList->addEntity(player);
    characterList->addEntity(spirit);    
    pCollision->includeEntity(static_cast<Entities::Entity*> (spirit));//explicit what it does, but it does automatic
    pCollision->setPlayer(player);
    Entities::Obstacles::Platform* floor = new Entities::Obstacles::Platform(sf::Vector2f(0.f, 500.f), sf::Vector2f(800.f, 50.f));
    Entities::Obstacles::Platform* platform1 = new Entities::Obstacles::Platform(sf::Vector2f(400.f, 390.f), sf::Vector2f(500.f, 50.f));
    Entities::Obstacles::Platform* platform2 = new Entities::Obstacles::Platform(sf::Vector2f(0.f, 450.f), sf::Vector2f(500.f, 50.f));
    Entities::Obstacles::Platform* platform3 = new Entities::Obstacles::Platform(sf::Vector2f(100.f, 100.f), sf::Vector2f(100.f, 100.f));


    obstacleList->addEntity(floor);
    obstacleList->addEntity(platform1);
    obstacleList->addEntity(platform2);
    obstacleList->addEntity(platform3);
    //change to just a entity list after, not obstacle and character

    pCollision->includeEntity(static_cast<Entities::Entity*> (floor));//explicit what it does, but it does automatic
    pCollision->includeEntity(static_cast<Entities::Entity*> (platform1));//explicit what it does, but it does automatic
    pCollision->includeEntity(static_cast<Entities::Entity*> (platform2));//explicit what it does, but it does automatic
    pCollision->includeEntity(static_cast<Entities::Entity*> (platform3));//explicit what it does, but it does automatic


    pEvent->setPlayer(player);
    Entities::Characters::Enemies::setPlayer(player);
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

        characterList->executeAll();
        obstacleList->executeAll();

        pCollision->run();
        
        pGraphic->clearWindow(); 
        characterList->drawAll(pGraphic->getWindow());
        obstacleList->drawAll(pGraphic->getWindow());
        pGraphic->showElements(); 
    }
}   

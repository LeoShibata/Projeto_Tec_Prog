#include "Game.hpp"
#include "Entities/Characters/Player.hpp"
#include "Entities/Obstacles/Platform.hpp"

    
using json = nlohmann::json;

Game::Game() : 
    pGraphic(Managers::GraphicManager::getGraphicManager()),
    pEvent(Managers::EventManager::getEventManager()),
    stage2(nullptr),
    stage1(nullptr)
{   
    if(pGraphic == nullptr) {
        std::cout << "ERROR: Failed to create graphic manager." << std::endl;
        exit(1);
    }

    stage2 = new Stages::BossRoom();
    stage1 = new Stages::Stage1();
}   

Game::~Game() {
    if(stage1) {
        delete stage1;
        stage1 = nullptr;
    }
}

void Game::run() {
    while (pGraphic->isWindowOpen()) {
        pEvent->run();

        if(stage1) {
            stage1->execute();
        }
        
        pGraphic->clearWindow(); 
        if(stage1) {
            stage1->draw(pGraphic->getWindow());
        } 
        pGraphic->showElements(); 
    }
}   

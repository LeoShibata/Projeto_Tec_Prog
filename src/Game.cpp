#include "Game.hpp"
#include "Entities/Characters/Player.hpp"
#include "Entities/Characters/Enemies/Spirit.hpp"
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
}   

Game::~Game() {
    if(stage2) {
        delete stage2;
        stage2 = nullptr;
    }
}

void Game::run() {
    while (pGraphic->isWindowOpen()) {
        pEvent->run();

        if(stage2) {
            stage2->execute();
        }
        
        pGraphic->clearWindow(); 
        if(stage2) {
            stage2->draw(pGraphic->getWindow());
        } 
        pGraphic->showElements(); 
    }
}   

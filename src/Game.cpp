#include "Game.hpp"
#include "Entities/Characters/Player.hpp"
#include "Entities/Characters/Enemies/Spirit.hpp"
#include "Entities/Obstacles/Platform.hpp"
#include "Stages/stage.hpp"
using json = nlohmann::json;

Game::Game() : 
    pGraphic(Managers::GraphicManager::getGraphicManager()),
    pEvent(Managers::EventManager::getEventManager()),
    stage(nullptr)
{   
    if(pGraphic == nullptr) {
        std::cout << "ERROR: Failed to create graphic manager." << std::endl;
        exit(1);
    }

    stage = new Stages::Stage();
}   

Game::~Game() {
    if(stage) {
        delete stage;
        stage = nullptr;
    }
}

void Game::run() {
    while (pGraphic->isWindowOpen()) {
        pEvent->run();

        if(stage) {
            stage->execute();
        }
        
        pGraphic->clearWindow(); 
        if(stage) {
            stage->draw(pGraphic->getWindow());
        } 
        pGraphic->showElements(); 
    }
}   

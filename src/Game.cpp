#include "Game.hpp"
#include "Entities/Characters/Player.hpp"
#include "Entities/Obstacles/Platform.hpp"

    
using json = nlohmann::json;

Game::Game() : 
    pGraphic(Managers::GraphicManager::getGraphicManager()),
    pEvent(Managers::EventManager::getEventManager()),
    castle(nullptr),
    graveyard(nullptr)
{   
    if(pGraphic == nullptr) {
        std::cout << "ERROR: Failed to create graphic manager." << std::endl;
        exit(1);
    }

    // castle = new Stages::Castle();
    graveyard = new Stages::Graveyard();
}   

Game::~Game() {
    if(graveyard) {
        delete graveyard;
        graveyard = nullptr;
    }
    if(castle) {
        delete castle;
        castle = nullptr;
    }
}

void Game::run() {
    while (pGraphic->isWindowOpen()) {
        pEvent->run();

        if(graveyard) {
            graveyard->execute();
        }
        
        pGraphic->clearWindow(); 
        if(graveyard) {
            graveyard->draw(pGraphic->getWindow());
        } 
        pGraphic->showElements(); 
    }
}   

#include "Game.hpp"
#include "Entities/Characters/Player.hpp"
#include "Entities/Obstacles/Platform.hpp"

    
using json = nlohmann::json;
using namespace std;

Game::Game() : 
    pGraphic(Managers::GraphicManager::getGraphicManager()),
    pEvent(Managers::EventManager::getEventManager()),
    pState(Managers::StateManager::getStateManager()),
    castle(nullptr),
    graveyard(nullptr)
{   
    if(pGraphic == nullptr) {
        std::cout << "ERROR: Failed to create graphic manager." << std::endl;
        exit(1);
    }

    cout <<" in game, created" << endl;
    pState->addState(0); // tela de menu
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
    if(pState){
        delete pState;
        pState = nullptr;
    }
}

void Game::run() {
    while (pGraphic->isWindowOpen()) {
        pGraphic->clearWindow(); 

        pEvent->run();

        pState->execute();

        /*if(castle) {
            castle->execute();
        }
        if(graveyard){
            graveyard->execute();
        }

        
        if(castle) {
            castle->draw(pGraphic->getWindow());
        } 
        if(graveyard)
            graveyard->draw(pGraphic->getWindow());*/
        //pGraphic->clearWindow(); 

        pGraphic->showElements(); 
    }
}   

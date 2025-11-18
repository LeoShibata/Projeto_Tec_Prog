#include "Managers/EventManager.hpp"
#include "Managers/StateManager.hpp"

namespace Managers {

EventManager* EventManager::pEvent = nullptr;

EventManager::EventManager() {
    pGraphic = GraphicManager::getGraphicManager();
    pState = StateManager::getStateManager();
    pPlayer = nullptr;
}

EventManager::~EventManager() { }

EventManager* EventManager::getEventManager() {
    if(pEvent == nullptr)
        pEvent = new EventManager();
    return pEvent;
}

void EventManager::setPlayer(Entities::Characters::Player* pPlayer) {
    this->pPlayer = pPlayer;
}

void EventManager::handleKeyPressed(sf::Keyboard::Key key) {
    //
}

void EventManager::handleKeyReleased(sf::Keyboard::Key key) {
    // 
}

void EventManager::run() {
    sf::Event event;
    while(pGraphic->getWindow()->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            pGraphic->closeWindow();
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            pGraphic->closeWindow();
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) 
        {
            if(pPlayer != nullptr) {
                pPlayer->jump();
            }
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            if(pPlayer != nullptr) {
                pPlayer->attack();
            }
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F){
            if(pPlayer != nullptr) 
                pPlayer->shoot();
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G){
            if(pPlayer != nullptr) 
                pState->addState(1);
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C){
            if(pPlayer != nullptr) 
                pState->addState(2);
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::H){
            if(pPlayer != nullptr) 
                pState->removeState(1);
        }
    }

    if(pPlayer == nullptr)
        return;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        pPlayer->startMovingLeft();
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        pPlayer->startMovingRight();
    else 
        pPlayer->stopMoving();
}

}
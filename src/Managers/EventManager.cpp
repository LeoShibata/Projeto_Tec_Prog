#include "Managers/EventManager.hpp"

namespace Managers {

EventManager* EventManager::pEvent = nullptr;

EventManager::EventManager() {
    pGraphic = GraphicManager::getGraphicManager();
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

void EventManager::setSpirit(Entities::Characters::Spirit* pSpirit) {
    this->pSpirit = pSpirit;
}

void EventManager::isKeyPressed(sf::Keyboard::Key key) {
    if(key == sf::Keyboard::A || key == sf::Keyboard::Left)
        pPlayer->moveLeft();
    else if(key == sf::Keyboard::D || key == sf::Keyboard::Right)
        pPlayer->moveRight();
    else if(key == sf::Keyboard::Escape)
        pGraphic->closeWindow();
}

void EventManager::isKeyReleased(sf::Keyboard::Key key) {
    }

void EventManager::run() {
    sf::Event event;
    while(pGraphic->getWindow()->pollEvent(event))
    {
        
        if(event.type == sf::Event::KeyPressed)
            isKeyPressed(event.key.code); 
        else if(event.type == sf::Event::KeyReleased)
            isKeyReleased(event.key.code);
        else if(event.type == sf::Event::Closed)
            pGraphic->closeWindow();

        pSpirit->followPlayer(pPlayer->getPos());

    }
}

}
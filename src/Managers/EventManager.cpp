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

void EventManager::setPlayer(Characters::Player* pPlayer) {
    this->pPlayer = pPlayer;
}

void EventManager::isKeyPressed(sf::Keyboard::Key key) {
    if(key == sf::Keyboard::A || key == sf::Keyboard::Left)
        pPlayer->move(true);
    else if(key == sf::Keyboard::D || key == sf::Keyboard::Right)
        pPlayer->move(false);
    else if(key == sf::Keyboard::Escape)
        pGraphic->closeWindow();
}

void EventManager::isKeyReleased(sf::Keyboard::Key key) {
    if(key == sf::Keyboard::A || key == sf::Keyboard::D || 
        key == sf::Keyboard::Left || key == sf::Keyboard::Right) 
        pPlayer->stop();
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
    }
}

}
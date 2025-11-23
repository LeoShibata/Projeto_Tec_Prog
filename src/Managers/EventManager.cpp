#include "Managers/EventManager.hpp"
#include "Managers/StateManager.hpp"

namespace Managers {


EventManager* EventManager::pEvent = nullptr;


EventManager::EventManager() {
    pGraphic = GraphicManager::getGraphicManager();
    pState = StateManager::getStateManager();
    pPlayer1 = nullptr;
    pPlayer2 = nullptr;
}


EventManager::~EventManager() { }


EventManager* EventManager::getEventManager() {
    if(pEvent == nullptr)
        pEvent = new EventManager();
    return pEvent;
}


void EventManager::setPlayer1(Entities::Characters::Player* pPlayer) {
    this->pPlayer1 = pPlayer;
}


void EventManager::setPlayer2(Entities::Characters::Player* pPlayer) {
    this->pPlayer2 = pPlayer;
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

        if(pPlayer1 != nullptr) {
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) {
                pPlayer1->jump();
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                pPlayer1->attack();
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F) {
                pPlayer1->shoot();
            }
        }

        if(pPlayer2 != nullptr) {
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                pPlayer2->jump();
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L) { 
                pPlayer2->attack();
            }            
            // if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::K) { 
            //     pPlayer2->shoot();
            // }
        }   
        // if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G) { 
        //         pState->addState(1);
        //     }
        // if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C) { 
        //         pState->addState(2);
        //     }
        // if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::H) { 
        //         pState->removeState(1);
        //     }
        // if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) { 
        //         pState->addState(3);
        //     }
    }

    if(pPlayer1 != nullptr) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            pPlayer1->startMovingLeft();
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            pPlayer1->startMovingRight();
        } else {
            pPlayer1->stopMoving();
        }
    }

    if(pPlayer2 != nullptr) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { 
            pPlayer2->startMovingLeft();
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { 
            pPlayer2->startMovingRight();
        } else { 
            pPlayer2->stopMoving();
        }
    }
}


}
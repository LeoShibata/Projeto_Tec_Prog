#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include "Managers/GraphicManager.hpp"
#include "Entities/Characters/Player.hpp"

namespace Managers {
    class StateManager;
    
    class EventManager {
        private:
            Managers::GraphicManager* pGraphic;
            Managers::StateManager* pState;
            Entities::Characters::Player* pPlayer1;
            Entities::Characters::Player* pPlayer2;
            static EventManager* pEvent;
        
            
        private:
            EventManager();

        public:
            ~EventManager();

            static EventManager* getEventManager();
            void setPlayer1(Entities::Characters::Player* pPlayer);
            void setPlayer2(Entities::Characters::Player* pPlayer);
            void handleKeyPressed(sf::Keyboard::Key key);
            void handleKeyReleased(sf::Keyboard::Key key);
        
            void run();
    };
}

#endif
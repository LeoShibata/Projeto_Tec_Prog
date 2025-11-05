#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include "Managers/GraphicManager.hpp"
#include "Entities/Characters/Player.hpp"
#include "Entities/Characters/Spirit.hpp"

namespace Managers {
    class EventManager {
        private:
            Managers::GraphicManager* pGraphic;
            Entities::Characters::Player* pPlayer;
            Entities::Characters::Spirit* pSpirit;

            static EventManager* pEvent;
        
        private:
            EventManager();

        public:
            ~EventManager();

            static EventManager* getEventManager();
            void setPlayer(Entities::Characters::Player* pPlayer);
            
            void handleKeyPressed(sf::Keyboard::Key key);
            void handleKeyReleased(sf::Keyboard::Key key);
            void run();
    };
}

#endif
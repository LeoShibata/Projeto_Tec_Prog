#ifndef GERENCIADOR_EVENTO_HPP
#define GERENCIADOR_EVENTO_HPP

#include "Managers/GraphicManager.hpp"
#include "Characters/Player.hpp"

namespace Managers {
    class EventManager {
        private:
             Managers::GraphicManager* pGraphic;
            Characters::Player* pPlayer;
            
            static EventManager* pEvent;
            EventManager();

        public:
            ~EventManager();

            static EventManager* getEventManager();
            void setPlayer(Characters::Player* pPlayer);
            
            void isKeyPressed(sf::Keyboard::Key key);
            void isKeyReleased(sf::Keyboard::Key key);
            void run();
    };
}

#endif
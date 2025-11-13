#ifndef GRAPHICMANAGER_HPP
#define GRAPHICMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#

namespace Entities::Characters {
    class Player; // para evitar include circular
}

namespace Managers {  
    class GraphicManager {
        private:
            sf::RenderWindow* window;
            static GraphicManager* pGraphic;
            sf::View view;
            Entities::Characters::Player* pPlayer;
            sf::Clock clock;
            float time;

        private:    
            GraphicManager();

        public:
            ~GraphicManager();
            
            static GraphicManager* getGraphicManager();
            sf::RenderWindow* getWindow();
            void setPlayer(Entities::Characters::Player* player);
            sf::Texture loadFileTexture(const char* pathtexture);

            bool isWindowOpen() const;
            void drawElement(const sf::RectangleShape& body);
            void showElements();
            void closeWindow();
            void clearWindow();
            void resetClock();
            const float getTime() const;
    };
}

#endif
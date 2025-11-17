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
            float time;
            sf::View view;
            sf::Clock clock;
            sf::RenderWindow* window;
            static GraphicManager* pGraphic;
            Entities::Characters::Player* pPlayer1;
            Entities::Characters::Player* pPlayer2;


        private:    
            GraphicManager();

        public:
            ~GraphicManager();
            
            static GraphicManager* getGraphicManager();
            sf::RenderWindow* getWindow();
            void setPlayer1(Entities::Characters::Player* player);
            void setPlayer2(Entities::Characters::Player* player);
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
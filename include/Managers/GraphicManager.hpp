#ifndef GRAPHICMANAGER_HPP
#define GRAPHICMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

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
            std::map<std::string, sf::Texture> textureMap;

        private:    
            GraphicManager();

        public:
            ~GraphicManager();
            
            static GraphicManager* getGraphicManager();
            sf::RenderWindow* getWindow();
            void setPlayer(Entities::Characters::Player* player);
            sf::Texture* loadFileTexture(const char* pathtexture);

            bool isWindowOpen() const;
            void drawElement(const sf::RectangleShape& body);
            void showElements();
            void closeWindow();
            void clearWindow();
    };
}

#endif
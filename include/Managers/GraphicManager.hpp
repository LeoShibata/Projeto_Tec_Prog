#ifndef GRAPHICMANAGER_HPP
#define GRAPHICMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

namespace Managers {  
    class GraphicManager {
        private:
            sf::RenderWindow* window;
            static GraphicManager* pGraphic;

            std::map<std::string, sf::Texture> textureMap;
            
        private:    
            GraphicManager();

        public:
            ~GraphicManager();
            
            static GraphicManager* getGraphicManager();
            sf::RenderWindow* getWindow();
            
            sf::Texture* loadFileTexture(const char* pathtexture);

            bool isWindowOpen() const;
            void drawElement(const sf::RectangleShape& body);
            void showElements();
            void closeWindow();
            void clearWindow();
    };
}

#endif
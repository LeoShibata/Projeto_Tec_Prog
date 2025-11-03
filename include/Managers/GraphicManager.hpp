#ifndef GRAPHICMANAGER_HPP
#define GRAPHICMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

namespace Managers {  
    class GraphicManager {
        private:
            sf::RenderWindow* window;
            static GraphicManager* pGraphic;
            GraphicManager();

        public:
            ~GraphicManager();
            
            static GraphicManager* getGraphicManager();
            sf::RenderWindow* getWindow();
            
            void clearWindow();
            void drawElement(const sf::RectangleShape& body);
            void showElements();
            void closeWindow();
            bool isWindowOpen() const;
    };
}

#endif
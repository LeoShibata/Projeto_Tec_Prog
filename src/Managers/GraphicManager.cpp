#include "Managers/GraphicManager.hpp"

namespace Managers {

GraphicManager* GraphicManager::pGraphic = nullptr;

GraphicManager::GraphicManager() :
    window(new sf::RenderWindow(sf::VideoMode(800.f, 600.f), "Game Test"))
{
    if(window == nullptr) {
        std::cout << "ERROR: Failed to create a graphics window." 
                  << std::endl;
        exit(1);
    }

    if(pGraphic == nullptr)
        pGraphic = this;
}   

GraphicManager::~GraphicManager() {
    if(window) {
        delete(window);
        window = nullptr;
    }
}

GraphicManager* GraphicManager::getGraphicManager() {
    if(pGraphic == nullptr) {
        pGraphic = new GraphicManager();
    }   
    return pGraphic;
}

sf::RenderWindow* GraphicManager::getWindow() {
    return window;
}

void GraphicManager::clearWindow() {
    window->clear();
}

void GraphicManager::drawElement(const sf::RectangleShape& body) {
    window->draw(body);
}

void GraphicManager::showElements() {
    window->display();
}

void GraphicManager::closeWindow() {
    window->close();
}

bool GraphicManager::isWindowOpen() const {
    return window->isOpen();
}

}
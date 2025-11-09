#include "Managers/GraphicManager.hpp"

#include <iostream>
using namespace std;

namespace Managers {

GraphicManager* GraphicManager::pGraphic = nullptr;

GraphicManager::GraphicManager() :
    window(new sf::RenderWindow(sf::VideoMode(1920.f, 1280.f), "Game Test"))
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

sf::Texture* GraphicManager::loadFileTexture(const char* pathtexture){
    std::string path(pathtexture);

    if(textureMap.count(path)) {
        return &textureMap[path];
    }

    sf::Texture newTexture;
    if(!newTexture.loadFromFile(pathtexture)) {
        std::cout << "ERROR: Failed to load texture from: " << pathtexture << std::endl;
        return nullptr;
    }

    textureMap[path] = newTexture;
    return &textureMap[path];
}

bool GraphicManager::isWindowOpen() const {
    return window->isOpen();
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

void GraphicManager::clearWindow() {
    window->clear(sf::Color::White);
}

}
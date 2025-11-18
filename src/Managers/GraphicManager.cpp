#include "Managers/GraphicManager.hpp"
#include "Entities/Characters/Player.hpp"

#include <iostream>
using namespace std;

namespace Managers {


GraphicManager* GraphicManager::pGraphic = nullptr;


GraphicManager::GraphicManager() :
    window(new sf::RenderWindow(sf::VideoMode(1280.f, 720.f), "Game Test")),
    view(),
    pPlayer1(nullptr),
    pPlayer2(nullptr)
{
    if(window == nullptr) {
        std::cout << "ERROR: Failed to create a graphics window." 
                  << std::endl;
        exit(1);
    }

    view.setSize(sf::Vector2f(640.f, 360.f));
    view.setCenter(sf::Vector2f(640.f, 360.f));
    
    // view.setSize(sf::Vector2f(1280.f, 720.f));
    // view.setCenter(sf::Vector2f(1280.f, 720.f));
    
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


void GraphicManager::setPlayer1(Entities::Characters::Player* player) {
    pPlayer1 = player;
}


void GraphicManager::setPlayer2(Entities::Characters::Player* player) {
    pPlayer2 = player;
}


sf::Texture GraphicManager::loadFileTexture(const char* pathtexture) {
    sf::Texture texture;
    if(!texture.loadFromFile(pathtexture)){
        std::cout << "ERROR, didnt found texture path, graphickManager - " << pathtexture << std::endl;
        exit(1); 
    }
    return texture;
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
    if(pPlayer1 && ! pPlayer2) {
        view.setCenter(pPlayer1->getPos());
    } else if (!pPlayer1 && pPlayer2) {
        view.setCenter(pPlayer2->getPos());
    } else if (pPlayer1 && pPlayer2) {
        sf::Vector2f midPoint = (pPlayer1->getPos() + pPlayer2->getPos()) / 2.f;
        view.setCenter(midPoint);
        // talvez adicionar mais coisas (zoom out)
    }
    window->setView(view);
    window->clear(sf::Color(100, 100, 100));
}


void GraphicManager::resetClock() {
    time = clock.getElapsedTime().asSeconds(); //to get as second, time = clock.restart()
    clock.restart();
}


const float GraphicManager::getTime() const {
    return time;
}


}
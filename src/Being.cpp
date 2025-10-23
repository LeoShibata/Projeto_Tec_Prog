#include "Being.hpp"           //  Nosso próprio header primeiro
#include "Managers/GraphicManager.hpp" // Headers locais depois
#include <iostream>            // Headers do sistema por últimoeam>

//init the class
Managers::GraphicManager* Being::pGraphic(Managers::GraphicManager::getGraphicManager());
int Being::cont = 0;
//namespace here

Being::Being(sf::Vector2f size): id(cont++), body(size) {
    //if change the rectangle shape, we put new commands here, to initiate the figure
}

Being::~Being() { }

const sf::RectangleShape& Being::getBody() const {
    return body;
}

const int Being::getId() const {
    return id;
}

void Being::draw() {
    pGraphic->drawElement(getBody()); //  try to use getbody after();
}
 
//...
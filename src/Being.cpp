#include "Being.hpp"           //  Nosso próprio header primeiro
#include "Managers/GraphicManager.hpp" // Headers locais depois

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

const sf::Vector2f Being::getPos() const {
    return body.getPosition(); 
}

const sf::Vector2f Being::getSize() const {
    return body.getSize();
}

void Being::draw() {
    pGraphic->drawElement(getBody()); //  try to use getbody after();
}
 
//...

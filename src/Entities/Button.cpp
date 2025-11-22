#include "Entities/Button.hpp" 

namespace Entities {


Button::Button(sf::Vector2f position, std::string info, const float textSize) :
    Entity(position, sf::Vector2f(0, 0), 0),
    selected(false)
{
    if(font.loadFromFile("../assets/fonts/OldeEnglish.ttf")) {
        text.setFont(font);
        text.setString(info);
        text.setCharacterSize(textSize);
        text.setFillColor(sf::Color::White);
        text.setPosition(position);
    } else {
        std::cout << "ERROR: Failed to load font." << std::endl;
    }
}


Button::~Button() { }


void Button::select(bool isSelected) { 
    selected = isSelected;
    if(selected) {
        text.setFillColor(sf::Color::Red);
    } else {
        text.setFillColor(sf::Color::White);
    }
}


void Button::execute() {
    Managers::GraphicManager::getGraphicManager()->getWindow()->draw(text);
}


void Button::update() { }


void Button::collision(Entity* other, float over, int collisionType) { }


}
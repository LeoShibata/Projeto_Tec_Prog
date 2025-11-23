#include "States/GameOverState.hpp"
#include "Managers/StateManager.hpp"
#include "Managers/GraphicManager.hpp"

namespace States {

GameOverState::GameOverState() :
    State(),
    currentOption(0)
{
    sf::Vector2u windowSize = pGraphic->getWindow()->getSize();
    background.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    background.setFillColor(sf::Color(30, 0, 0, 180));

    if(!font.loadFromFile("../assets/fonts/OldeEnglish.ttf")) {
        std::cout << "ERROR: Failed to load GameOver font" << std::endl;
        exit(1);
    }

    titleText.setFont(font);
    titleText.setString("GAME OVER");
    titleText.setCharacterSize(80);
    titleText.setFillColor(sf::Color::Red);
    titleText.setOutlineColor(sf::Color::Black);
    titleText.setOutlineThickness(2);

    sf::FloatRect textRect = titleText.getLocalBounds();
    titleText.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
    titleText.setPosition(windowSize.x / 2.f, 150);

    buttons.push_back(new Entities::Button(sf::Vector2f(windowSize.x / 2.f, 350), "Back to Menu"));
    buttons.push_back(new Entities::Button(sf::Vector2f(windowSize.x / 2.f, 450), "Exit Game"));

    if(!buttons.empty()) {
        buttons[0]->select(true);
    }
}


GameOverState::~GameOverState() {
    for(int i = 0; i < buttons.size(); i++) {
        Entities::Button* btn = buttons[i];
        delete btn;
    }
    buttons.clear();
}


void GameOverState::draw() { 
    pGraphic->getWindow()->draw(background);
    pGraphic->getWindow()->draw(titleText);

    for(int i = 0; i < buttons.size(); i++) {
        Entities::Button* btn = buttons[i];
        btn->execute();
    }
}

void GameOverState::execute() {
    resetView();

    draw();

    if(inputClock.getElapsedTime().asSeconds() > 0.2f) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            buttons[currentOption]->select(false);
            currentOption--;
            if(currentOption < 0) currentOption = buttons.size() - 1;
            buttons[currentOption]->select(true);
            inputClock.restart();
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            buttons[currentOption]->select(false);
            currentOption++;
            if(currentOption >= buttons.size()) currentOption = 0;
            buttons[currentOption]->select(true);
            inputClock.restart();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            if(currentOption == 0) { 
                pStateManager->removeState(2); 
                return;
            } 
            else if (currentOption == 1) { 
                pGraphic->closeWindow();
            }
            inputClock.restart();
        }
    }
}

}
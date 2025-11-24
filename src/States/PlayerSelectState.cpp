#include "States/PlayerSelectState.hpp"
#include "States/StatePlaying.hpp"
#include "Managers/StateManager.hpp"
#include "Managers/GraphicManager.hpp"

namespace States {

PlayerSelectState::PlayerSelectState() : 
    State(),
    currentOption(0)
{   
    sf::Vector2u windowSize = pGraphic->getWindow()->getSize();
    background.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    background.setFillColor(sf::Color(20, 20, 20));

    if(font.loadFromFile("../assets/fonts/OldeEnglish.ttf")) {
        instructionText.setFont(font);
        instructionText.setString("Select Mode: ");
        instructionText.setCharacterSize(60);
        instructionText.setFillColor(sf::Color::White);
        sf::FloatRect rect = instructionText.getLocalBounds();
        instructionText.setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
        instructionText.setPosition(windowSize.x/2.0f, 150);
    }

    buttons.push_back(new Entities::Button(sf::Vector2f(550, 300), "1 Player"));
    buttons.push_back(new Entities::Button(sf::Vector2f(550, 400), "2 Players"));

    if(!buttons.empty()) {
        buttons[0]->select(true);
    }
}


PlayerSelectState::~PlayerSelectState() { 
    for(int i = 0; i < buttons.size(); i++) {
        Entities::Button* btn = buttons[i];
        delete btn;
    }
    buttons.clear();
}


void PlayerSelectState::draw() {
    pGraphic->getWindow()->draw(background);
    pGraphic->getWindow()->draw(instructionText);
}


void PlayerSelectState::execute() {
    resetView();
    draw();

    for(int i = 0; i < buttons.size(); i++) {
        Entities::Button* btn = buttons[i];
        btn->execute();
    }

    if(inputClock.getElapsedTime().asSeconds() > 0.2f) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            buttons[currentOption]->select(false);
            currentOption--;
            if(currentOption < 0) {
                currentOption = buttons.size() - 1;
            }
            buttons[currentOption]->select(true);
            inputClock.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            buttons[currentOption]->select(false);
            currentOption++;
            if(currentOption >= buttons.size()) {
                currentOption = 0;
            }
            buttons[currentOption]->select(true);
            inputClock.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            if(currentOption == 0) {
                StatePlaying::playersCount = 1;
            } else {
                StatePlaying::playersCount = 2;
            }
            
            pStateManager->removeState(); // para botao voltar    
            pStateManager->addState(5); // vai para seleção de fase
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            pStateManager->removeState();
            inputClock.restart();
        }
    }
}

}
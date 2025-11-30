#include "States/StageSelectState.hpp"
#include "Managers/StateManager.hpp"
#include "Managers/GraphicManager.hpp"

namespace States {

StageSelectState::StageSelectState() :
    State(),
    currentOption(0)
{
    sf::Vector2u windowSize = pGraphic->getWindow()->getSize();
    background.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    background.setFillColor(sf::Color(20, 20, 20));
    
    if(font.loadFromFile("../assets/fonts/OldeEnglish.ttf")) {
        titleText.setFont(font);
        titleText.setString("Choose Stage: ");
        titleText.setCharacterSize(60);
        titleText.setFillColor(sf::Color::White);
        sf::FloatRect rect = titleText.getLocalBounds();
        titleText.setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
        titleText.setPosition(windowSize.x / 2.0f, 150);
    }
    
    if(!font.loadFromFile("../assets/fonts/OldeEnglish.ttf")) {
        std::cout << "ERROR: Faild to load Stage Select font." << std::endl;
        exit(1);
    }

    buttons.push_back(new Entities::Button(sf::Vector2f(550, 300), "Stage 1 - Graveyard"));
    buttons.push_back(new Entities::Button(sf::Vector2f(550, 400), "Stage 2 - Castle"));

    if(!buttons.empty()) {
        buttons[0]->select(true);
    }
}


StageSelectState::~StageSelectState() { }


void StageSelectState::draw() {
    pGraphic->getWindow()->draw(background);
    pGraphic->getWindow()->draw(titleText);
}


void StageSelectState::execute() { 
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
            // Opção 0: Fase 1 (ID 1)
            // Opção 1: Fase 2 (ID 2)
            int idFase;
            if(currentOption == 0) {
                idFase = 1;
            } else {
                idFase = 2;
            }
            
            // Remove a seleção de fase da pilha para não voltar pra ela no pause/gameover
            pStateManager->removeState();
            pStateManager->addState(idFase);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            pStateManager->removeState();
            inputClock.restart();
        }
    }
}

}
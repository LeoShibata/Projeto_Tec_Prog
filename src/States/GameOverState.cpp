#include "States/GameOverState.hpp"

#include "States/StatePlaying.hpp"
#include "Managers/StateManager.hpp"
#include "Managers/GraphicManager.hpp"
#include "Stages/Stage.hpp"

namespace States {

GameOverState::GameOverState() :
    State(),
    currentOption(0),
    playerName(""),
    nameEntered(false),
    finalScore(0)
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


    // Configurações do texto de input de nome
    nameText.setFont(font);
    nameText.setCharacterSize(40);
    nameText.setFillColor(sf::Color::Yellow);
    // Centraliza ou posiciona onde desejar
    nameText.setPosition(windowSize.x / 2.f - 150, 300);
    nameText.setString("Enter Name: ");


    buttons.push_back(new Entities::Button(sf::Vector2f(windowSize.x / 2.f, 500), "Back to Menu"));
    buttons.push_back(new Entities::Button(sf::Vector2f(windowSize.x / 2.f, 600), "Exit Game"));

    if(!buttons.empty()) {
        buttons[0]->select(true);
    }

    
    if(States::StatePlaying::pCurrentStage) {
        auto p1 = States::StatePlaying::pCurrentStage->getPlayer1();
        auto p2 = States::StatePlaying::pCurrentStage->getPlayer2();
        
        if(p1) {
            finalScore += p1->getScore();
        }
        if(p2) {
            finalScore += p2->getScore();
        }
        
        // std::cout << "Final Score retrieved: " << finalScore << std::endl;
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

    if(!nameEntered) {
        pGraphic->getWindow()->draw(nameText);
    } else {
        for(int i = 0; i < buttons.size(); i++) {
            Entities::Button* btn = buttons[i];
            btn->execute();
        }
    }
}

void GameOverState::execute() {
    resetView();

    if(!nameEntered) {
        nameText.setString("Enter Name: " + playerName);
    }

    draw();

    if(inputClock.getElapsedTime().asSeconds() > 0.2f) {
        if(!nameEntered) { // Lógica de digitação do nome
            // Captura A-Z
            for(int k = sf::Keyboard::A; k <= sf::Keyboard::Z; ++k) {
                if(sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k))) {
                    if(playerName.size() < 10) { // Limite de caracteres
                        playerName += (char)('A' + (k - sf::Keyboard::A));
                        inputClock.restart();
                    }
                }
            }
            // Backspace para apagar
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && playerName.size() > 0) {
                playerName.pop_back();
                inputClock.restart();
            }
            // Enter para confirmar
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && playerName.size() > 0) {
                nameEntered = true;

                // Salva no Leaderboard
                leaderboard.addEntry(playerName, finalScore);
                std::cout << "Score saved: " << playerName << " - " << finalScore << std::endl;

                inputClock.restart();
            }
        } else {  // Lógica dos botões - funciona apenas se colocar o nome
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
                    pStateManager->removeState(2); 
                    return;
                } 
                else if(currentOption == 1) { 
                    pGraphic->closeWindow();
                }
                inputClock.restart();
            }
        }
    }
}

}
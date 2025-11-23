#include "States/StatePause.hpp"
#include "Managers/StateManager.hpp"
#include "Managers/GraphicManager.hpp" 

using namespace std;

namespace States {

StatePause::StatePause() {
    // fundo escuro semi-transparente
    std::cout << "[DEBUG] StatePause Criado" << std::endl;

    sf::Vector2u windowSize = pGraphic->getWindow()->getSize();
    background.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    background.setFillColor(sf::Color(0, 0, 0, 150));

    // carrega fonte e título
    if (!font.loadFromFile("../assets/fonts/OldeEnglish.ttf")) {
        cout << "ERROR: Could not load font in StatePause." << endl;
    }

    titleText.setFont(font);
    titleText.setString("PAUSED");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);
    
    // Center the origin of the text object
    sf::FloatRect textRect = titleText.getLocalBounds();
    titleText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    titleText.setPosition(windowSize.x / 2.f, 200);

    // cria botões 
    buttons.push_back(new Entities::Button(sf::Vector2f(windowSize.x / 2.f, 350), "Resume"));
    buttons.push_back(new Entities::Button(sf::Vector2f(windowSize.x / 2.f, 450), "Quit to Menu"));

    if(!buttons.empty()) {
        buttons[0]->select(true);
    }
}


StatePause::~StatePause() { 
    std::cout << "[DEBUG] StatePause Destruido" << std::endl;
    for(int i = 0; i < buttons.size(); i++) {
        Entities::Button* btn = buttons[i];
        delete btn;
    }
    buttons.clear();
}


void StatePause::draw() {
    pGraphic->getWindow()->draw(background);
    pGraphic->getWindow()->draw(titleText);

    for(int i = 0; i < buttons.size(); i++) {
        Entities::Button* btn = buttons[i];
        btn->execute();
    }
}


void StatePause::execute(){
    // centraliza camera
    resetView();

    draw();

    if(inputClock.getElapsedTime().asSeconds() > 0.5f) {
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
            if(currentOption >= buttons.size()) currentOption = 0;
            buttons[currentOption]->select(true);
            inputClock.restart();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            if(currentOption == 0) { // RESUME
                pStateManager->removeState(); // Remove o Pause, volta pro Jogo
                return;
            } 
            else if (currentOption == 1) { // QUIT TO MENU
                pStateManager->removeState(2); 
                return;
            }
            inputClock.restart();
        }
    }
}

}

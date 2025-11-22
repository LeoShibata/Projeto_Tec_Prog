#include "States/StateMenu.hpp"
#include "Managers/StateManager.hpp"
#include "Managers/GraphicManager.hpp" // Make sure to include this

namespace States {

StateMenu::StateMenu() : 
    State(), 
    currentOption(0)
{
    if(!bgTexture.loadFromFile("../assets/stages/Graveyard/Background_0.png")) {
        std::cout << "ERROR: Could not open menu background texture." << std::endl;
    }
    background.setTexture(&bgTexture);
    sf::Vector2u windowSize = pGraphic->getWindow()->getSize();
    background.setSize(sf::Vector2f(windowSize.x, windowSize.y));

    if(font.loadFromFile("../assets/fonts/OldeEnglish.ttf")) {
        titleText.setFont(font);
        titleText.setString("MOONLIGHT"); // Nome do jogo
        titleText.setCharacterSize(80);
        titleText.setFillColor(sf::Color::Red); // Cor de destaque
        titleText.setOutlineColor(sf::Color::Black);
        titleText.setOutlineThickness(3);
        
        // Centralizar
        sf::FloatRect textRect = titleText.getLocalBounds();
        titleText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
        titleText.setPosition(sf::Vector2f(windowSize.x / 2.0f, 100.0f)); // Mais no topo
    }

    buttons.push_back(new Entities::Button(sf::Vector2f(550, 300), "New Game"));
    buttons.push_back(new Entities::Button(sf::Vector2f(550, 400), "Exit"));

    if(!buttons.empty()) {
        buttons[0]->select(true);
    }
}


StateMenu::~StateMenu() {
    for(int i = 0; i < buttons.size(); i++) {
        Entities::Button* btn = buttons[i];
        delete btn;
    }
    buttons.clear();
}

void StateMenu::execute(){
    sf::View defaultView = pGraphic->getWindow()->getDefaultView();
    pGraphic->getWindow()->setView(defaultView);
    
    pGraphic->getWindow()->draw(background);
    pGraphic->getWindow()->draw(titleText);

    for(int i = 0; i < buttons.size(); i++) {
        Entities::Button* btn = buttons[i];
        btn->execute();
    }

    if(inputClock.getElapsedTime().asSeconds() > 0.2f) { // delay pra nao trocar rapido demais
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { // para cima
            buttons[currentOption]->select(false);
            currentOption--;
            if(currentOption < 0) {
                currentOption = buttons.size() - 1;
            }
            buttons[currentOption]->select(true);
            inputClock.restart();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { // para cima
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
                pStateManager->addState(4);   // novo jogo: vai para seleção de players (ID 4)
            } else if (currentOption == 1) {
                pStateManager->removeState(); // SAIR
            }
            inputClock.restart();
        }
    }
}


void StateMenu::draw() { }

}


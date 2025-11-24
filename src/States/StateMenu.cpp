#include "States/StateMenu.hpp"
#include "States/StatePlaying.hpp"
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
        titleText.setCharacterSize(120);
        titleText.setFillColor(sf::Color::White); // Cor de destaque
        titleText.setOutlineColor(sf::Color::Black);
        titleText.setOutlineThickness(5);
        
        // Centralizar
        sf::FloatRect textRect = titleText.getLocalBounds();
        titleText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
        titleText.setPosition(sf::Vector2f(windowSize.x / 2.0f, 140.0f)); // Mais no topo
    }

    buttons.push_back(new Entities::Button(sf::Vector2f(550, 250), "New Game"));
    buttons.push_back(new Entities::Button(sf::Vector2f(550, 350), "Load Game"));
    buttons.push_back(new Entities::Button(sf::Vector2f(550, 450), "Leaderboard"));
    buttons.push_back(new Entities::Button(sf::Vector2f(550, 550), "Exit"));

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
    resetView();

    if(inputClock.getElapsedTime().asSeconds() > 1.f) {
        inputClock.restart();
    }
    
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
            if(currentOption == 0) { // NEW GAME
                pStateManager->addState(4);   
            } 
            else if(currentOption == 1) { // LOAD GAME
                pStateManager->addState(1); 
                States::StatePlaying* playingState = static_cast<States::StatePlaying*>(pStateManager->getAtualState());
                if(playingState) {
                    playingState->loadStage(); 
                }                
            }else if (currentOption == 2) { // LEADERBOARD
                pStateManager->addState(7); 
                return;
            } else if (currentOption == 3) { // EXIT
                pStateManager->removeState(); 
                return;
            }
            inputClock.restart();
            
    
            
            


        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        //     pGraphic->closeWindow();
        // }
    }


    }
}
void StateMenu::draw() { }

}


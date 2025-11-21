#include "States/StateMenu.hpp"
#include "Managers/StateManager.hpp"
#include "Managers/GraphicManager.hpp" // Make sure to include this

using namespace States;
using namespace std;
StateMenu::StateMenu(): Being(sf::Vector2f(0,0)){
    /*bgTexture.loadFromFile("../assets/stages/Graveyard/Background_0.png");
    background.setTexture(&bgTexture);
    background.setSize(sf::Vector2f(bgTexture.getSize().x, bgTexture.getSize().y));
    background.setPosition(0.f, 0.f);
    sf::RenderWindow* window = State::pGraphic->getWindow();*/

}

StateMenu::~StateMenu(){

}

void StateMenu::createNewWindow(){
    int option;
    cout << "enter the stage number" << endl;
    cin >> option;
    
    
    if (option == 1)
    {
        pStateManager->addState(1);
    }else{
        pStateManager->addState(2);
    }
    
}

void StateMenu::execute(){
    //window->draw(background);
    createNewWindow();
    
    
    //Being::draw();

}
#include "States/StatePause.hpp"
#include "Managers/StateManager.hpp"
#include "Managers/GraphicManager.hpp" // Make sure to include this

using namespace std;

namespace States {

StatePause::StatePause() {
    // LOAD FONT
    // Ensure this path is correct for your project folder structure
    if (!font.loadFromFile("../assets/fonts/OldeEnglish.ttf")) {
        cout << "ERROR: Could not load font in StatePause." << endl;
    }

    // SETUP TEXT
    text.setFont(font);
    text.setString("PAUSED");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    
    // Center the origin of the text object
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
}


StatePause::~StatePause() { }


void StatePause::execute(){
    // 1. Get Window and View
    sf::RenderWindow* window = pGraphic->getWindow();
    sf::View view = window->getView();

    // 2. Set text position to center of the camera
    text.setPosition(view.getCenter());

    // 3. Draw
    // Note: The background will be the clear color (Gray) because 
    // StateManager isn't drawing StatePlaying right now.
    window->draw(text);
}

}

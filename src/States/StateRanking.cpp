#include "States/StateRanking.hpp"
#include "Managers/StateManager.hpp"
#include "Managers/GraphicManager.hpp"

namespace States {

StateRanking::StateRanking() :
    State()
{ 
    sf::Vector2u windowSize = pGraphic->getWindow()->getSize();
    
    if(!font.loadFromFile("../assets/fonts/OldeEnglish.ttf")) {
        exit(1);
    }

    titleText.setFont(font);
    titleText.setString("LEADERBOARD");
    titleText.setCharacterSize(60);
    titleText.setPosition(450, 50);

    background.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    background.setFillColor(sf::Color(20, 20, 20));

    auto scores = leaderboard.getScores();
    for(int i = 0; i < scores.size(); i++) {
        sf::Text t;
        t.setFont(font);
        t.setString(std::to_string(i+1) + ". " + scores[i].name + " - " + std::to_string(scores[i].score));
        t.setCharacterSize(40);
        t.setPosition(400, 150 + i * 60);
        scoreTexts.push_back(t);
    }
    
    // Adicionar uma instrução para voltar!!!!!!!!!!!!
    sf::Text back;
    back.setFont(font);
    back.setString("Press ESC to return");
    back.setPosition(400, 600);
    scoreTexts.push_back(back);
}


StateRanking::~StateRanking() { }


void StateRanking::draw() {
    pGraphic->getWindow()->draw(background);
    pGraphic->getWindow()->draw(titleText);

    for(size_t i = 0; i < scoreTexts.size(); i++) {
        pGraphic->getWindow()->draw(scoreTexts[i]);
    }
}


void StateRanking::execute() {
    resetView();
    draw();
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        pStateManager->removeState();
    }
}

} // namespace States 
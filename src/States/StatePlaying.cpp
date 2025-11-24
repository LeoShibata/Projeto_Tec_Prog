#include "States/StatePlaying.hpp"
#include "Managers/StateManager.hpp"

// here i decide to put a connection with stage by pointer instead of heritance
// thats because i really wanted to try and play with passing pointers using singleton, and
// practicing how to evit reclusive include and bidirectional connections.
// And in this, there will not be a figure or id to use, i don't think the methods in my Being super class would translate
// well in here, of course it would make it easier to use my graphicManager, but that is basically the only thing i would use
// from that class, instead, in menu i will create shapes and sprites, will draw and need get some ids, so here
// it will continue with pointer, while in menu its going be via heritance;

namespace States {

int StatePlaying::playersCount = 1;
Stages::Stage* StatePlaying::pCurrentStage = nullptr;

StatePlaying::StatePlaying(int idStage) : 
    idStage(idStage),
    stages()
{
    createStage();

    if(!stages.empty()) {
        pCurrentStage = stages.front();
    }
}


StatePlaying::~StatePlaying() {
    if(pCurrentStage == stages.front()) {
        pCurrentStage = nullptr;
    }

    State::pGraphic->clearWindow();

    while(!(stages.empty())) {
        delete(stages.front());
        stages.front() = nullptr;
        stages.pop();
    }
    
}


void StatePlaying::createStage() {
    if(idStage == 1) {
        Stages::Stage* newStage = static_cast<Stages::Stage*>(new Stages::Graveyard());
        stages.push(newStage);
    } else {
        Stages::Stage* newStage = static_cast<Stages::Stage*>(new Stages::Castle());
        stages.push(newStage);
    }
}


void StatePlaying::loadStage() { 
    std::ifstream file("savegame.json");
    if (!file.is_open()) {
        std::cout << "ERROR: Save file not found." << std::endl;
        return;
    }

    nlohmann::json j;
    file >> j;
    file.close();

    int savedLevel = 1; 
    if(j.contains("levelId")) {
        savedLevel = j["levelId"];
    }

    if (savedLevel != this->idStage) {
        std::cout << "[DEBUG] Switching Stage from " << this->idStage << " to " << savedLevel << std::endl;
        
        if (!stages.empty()) {
            delete stages.front();
            stages.pop();
        }

        this->idStage = savedLevel;
        createStage(); 
    }

    if(pCurrentStage) {
        pCurrentStage->loadGame();
    }
}

void StatePlaying::execute() {
    if(stages.empty()) {
        return;
    }

    stages.front()->execute();
    stages.front()->draw(pGraphic->getWindow());

    if((sf::Keyboard::isKeyPressed(sf::Keyboard::P) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) && 
        inputClock.getElapsedTime().asSeconds() > 0.5f) 
    {
        pStateManager->addState(3); // add pause (ID 3)
        inputClock.restart();
    }
}

}

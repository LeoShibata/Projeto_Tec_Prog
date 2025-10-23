#include "Game.hpp"

Game::Game() : 
    characters(),
    pGraphic(Managers::GraphicManager::getGraphicManager()),
    pEvent(Managers::EventManager::getEventManager())
{   
    if(pGraphic == nullptr) {
        std::cout << "ERROR: Failed to create graphic manager." << std::endl;
        exit(1);
    }

    Characters::Player* player = new Characters::Player(sf::Vector2f(100.f, 200.f), sf::Vector2f(50.f, 50.f));
    Characters::Character* p1 = static_cast<Characters::Character*>(player);
    characters.push_back(p1);

    pEvent->setPlayer(player);
}   

Game::~Game() {
    for (int i = 0; i < characters.size(); i++) {
        delete characters[i];
    }
    characters.clear();
}

void Game::run() {
    while (pGraphic->isWindowOpen())
    {
        pEvent->run();
        pGraphic->clearWindow(); 
        for(int i = 0; i < characters.size(); i++) {
            characters[i]->execute();
            characters[i]->draw();
        }
        pGraphic->showElements(); 
    }
    characters.clear();
}   
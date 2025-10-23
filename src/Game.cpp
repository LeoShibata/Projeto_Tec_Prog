#include "Game.hpp"

Game::Game() : 
    characters(),
    pGraphic(Managers::GraphicManager::getGraphicManager())
{   
    if(pGraphic == nullptr) {
        std::cout << "ERROR: Failed to create graphic manager." << std::endl;
        exit(1);
    }

    Characters::Player* player = new Characters::Player(2.f, sf::Vector2f(100.f, 200.f), sf::Vector2f(50.f, 50.f));
    Characters::Character* p1 = static_cast<Characters::Character*>(player);
    characters.push_back(p1);
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
        sf::Event event;
        while(pGraphic->getWindow()->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                pGraphic->closeWindow(); 

            else if(event.type == sf::Event::KeyPressed 
                && event.key.code == sf::Keyboard::Escape)
                pGraphic->closeWindow();
	    }

        pGraphic->clearWindow(); 
        for(int i = 0; i < characters.size(); i++) {
            characters[i]->move();
            pGraphic->drawElement(characters[i]->getBody());
        }
        pGraphic->showElements(); 
    }
    characters.clear();
}   

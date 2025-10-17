#include "Jogo.hpp"

Jogo::Jogo() : 
    window(sf::VideoMode(800.f, 600.f), "Teste - Jogo"),
    personagens()
{   
    Jogador* jogador = new Jogador(sf::Vector2f(100.f, 200.f), sf::Vector2f(50.f, 50.f));

    Personagem* p1 = static_cast<Personagem*>(jogador);

    personagens.push_back(p1);
}   

Jogo::~Jogo() {
    for (int i = 0; i < personagens.size(); i++) {
        delete personagens[i];
    }
    personagens.clear();
}

void Jogo::executar() {
    while (window.isOpen())
    {
        sf::Event evento;
        while(window.pollEvent(evento))
        {
            if(evento.type == sf::Event::Closed)
                window.close();

            else if(evento.type == sf::Event::KeyPressed 
                && evento.key.code == sf::Keyboard::Escape)
                window.close();
	    }

        window.clear(); 
        for(int i = 0; i < personagens.size(); i++) {
            personagens[i]->move();
            window.draw(personagens[i]->getCorpo());
        }
        window.display(); 
    }
    personagens.clear();
}   
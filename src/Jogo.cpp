#include "Jogo.hpp"

Jogo::Jogo() : 
    window(sf::VideoMode(800, 600), "Teste - Jogo"),
    jogador(sf::Vector2f(0.f, 0.f), sf::Vector2f(50.f, 50.f))
{
    executar();
}   

Jogo::~Jogo() {

}

void Jogo::executar() {
    while (window.isOpen())
    {
        sf::Event evento;
        if(window.pollEvent(evento))
        {
            if(evento.type == sf::Event::Closed) {
                window.close();
            }

            else if(evento.type == sf::Event::KeyPressed) {
                if (evento.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
	    }

        window.clear(); 
        jogador.move();
        window.draw(jogador.getCorpo());
        window.display(); 
    }
}   
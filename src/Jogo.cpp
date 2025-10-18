#include "Jogo.hpp"

Jogo::Jogo() : 
    //window(sf::VideoMode(800.f, 600.f), "Teste - Jogo"),
    personagens(),
    pGrafico(Gerenciador_Grafico::getGerenciadorGrafico())
{   
    if(pGrafico == nullptr) {
        std::cout << "ERROR: Nao foi possivel criar o gerenciador grafico" << std::endl;
        exit(1);
    }

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
    while (pGrafico->verificaJanelaAberta())
    {
        sf::Event evento;
        while(pGrafico->getWindow()->pollEvent(evento))
        {
            if(evento.type == sf::Event::Closed)
                pGrafico->fecharJanela(); 

            else if(evento.type == sf::Event::KeyPressed 
                && evento.key.code == sf::Keyboard::Escape)
                pGrafico->fecharJanela();
	    }

        pGrafico->limpaJanela(); 
        for(int i = 0; i < personagens.size(); i++) {
            personagens[i]->move();
            pGrafico->desenhaElemento(personagens[i]->getCorpo());
        }
        pGrafico->mostraElementos(); 
    }
    personagens.clear();
}   
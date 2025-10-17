#ifndef JOGO_HPP
#define JOGO_HPP

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include "Personagens/Jogador/Jogador.hpp"
#include "Personagens/Personagem.hpp"

class Jogo {
    private:
        sf::RenderWindow window;  
        std::vector<Personagem*> personagens;
        // Jogador jogador;

    public:
        Jogo ();
        ~Jogo ();
        void executar ();
};

#endif
#ifndef JOGO_HPP
#define JOGO_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Personagens/Jogador.hpp"

class Jogo {
    private:
        sf::RenderWindow window;  
        Jogador jogador;

    public:
        Jogo ();
        ~Jogo ();
        void executar ();
};

#endif
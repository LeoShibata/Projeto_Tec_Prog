#ifndef JOGO_HPP
#define JOGO_HPP

#include <iostream>
#include <vector>

#include <Gerenciadores/Gerenciador_Grafico.hpp>
#include "Personagens/Jogador/Jogador.hpp"
#include "Personagens/Personagem.hpp"

class Jogo {
    private:
        Gerenciador_Grafico* pGrafico; 
        std::vector<Personagem*> personagens;

    public:
        Jogo ();
        ~Jogo ();
        void executar ();
};

#endif
#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include "Personagens/Personagem.hpp"

#include <iostream>

class Jogador : public Personagem {
    private:
        void inicializa();
    
    public:
        Jogador(const sf::Vector2f pos, const sf::Vector2f tam);
        Jogador();
        ~Jogador();
        const sf::RectangleShape& getCorpo() const override;
        void move() override;
};

#endif
#include "Personagens/Personagem.hpp"

Personagem::Personagem(const sf::Vector2f pos, const sf::Vector2f tam) {
    corpo.setSize(tam);
    corpo.setPosition(pos);
    corpo.setFillColor(sf::Color::Green);
    vel = sf::Vector2f(0.f, 0.f);
}

Personagem::~Personagem() { }

const sf::RectangleShape& Personagem::getCorpo() const {
    return corpo;
}

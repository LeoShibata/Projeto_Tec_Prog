#include "Personagens/Jogador.hpp"

Jogador::Jogador (const sf::Vector2f pos, const sf::Vector2f tam) :
    corpo(sf::RectangleShape(tam))
{
    corpo.setPosition(pos);
    corpo.setFillColor(sf::Color::Magenta);
    inicializa();
}

Jogador::Jogador (const sf::RectangleShape corpo) :
    corpo (corpo)
{
    inicializa();
}

Jogador::Jogador() : 
    corpo () 
{
    inicializa();
}

Jogador::~Jogador() {

}

void Jogador::inicializa() {
    vel = sf::Vector2f(0.6f, 0.6f);
}

const sf::RectangleShape Jogador::getCorpo() {
    return corpo;
}

void Jogador::move() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
    {
        corpo.move(-vel.x, 0.f);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
    {
        corpo.move(vel.x, 0.f);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
    {
        corpo.move(0.f, -vel.y);
    } 
    
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
    {
        corpo.move(0.f, vel.y);
    }
}
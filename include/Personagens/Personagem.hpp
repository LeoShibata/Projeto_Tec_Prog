#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include <SFML/Graphics.hpp>

class Personagem {
    protected:
        sf::RectangleShape corpo;
        sf::Vector2f vel;

    public:
        Personagem(const sf::Vector2f pos, const sf::Vector2f tam);
        virtual ~Personagem();
        virtual const sf::RectangleShape& getCorpo() const;
        virtual void move() = 0;
};

#endif
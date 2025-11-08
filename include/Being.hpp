#ifndef BEING_HPP
#define BEING_HPP

#include <SFML/Graphics.hpp>
#include "Managers/GraphicManager.hpp"
#include <stdio.h>
using namespace std;

class Being {
    protected:  
        static Managers::GraphicManager* pGraphic;
        sf::RectangleShape body;
        const int id;
        static int cont;
        sf::Texture texture;

    public:
        Being(sf::Vector2f size);
        virtual ~Being();

        virtual const sf::RectangleShape& getBody() const;
        const int getId() const;
        const sf::Vector2f getPos() const;
        const sf::Vector2f getSize() const;
        void draw();

        virtual void execute() = 0; 
};

#endif

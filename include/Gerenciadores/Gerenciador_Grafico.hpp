#ifndef GERENCIADOR_GRAFICO_HPP
#define GERENCIADOR_GRAFICO_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Gerenciador_Grafico {
    private:
        sf::RenderWindow* window;
        static Gerenciador_Grafico* pGrafico;
        Gerenciador_Grafico();
    
    public:
        ~Gerenciador_Grafico();
       
        static Gerenciador_Grafico* getGerenciadorGrafico();
        sf::RenderWindow* getWindow();
       
        void limpaJanela();
        void desenhaElemento(const sf::RectangleShape corpo);
        void mostraElementos();
        void fecharJanela();
        bool verificaJanelaAberta() const;
};

#endif
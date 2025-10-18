#include "Gerenciadores/Gerenciador_Grafico.hpp"

Gerenciador_Grafico* Gerenciador_Grafico::pGrafico = nullptr;

Gerenciador_Grafico::Gerenciador_Grafico() :
    window(new sf::RenderWindow(sf::VideoMode(800.f, 600.f), "Teste - Jogo"))
{
    if(window == nullptr) {
        std::cout << "ERROR: Nao foi possivel criar uma janela grafica." 
                  << std::endl;
        exit(1);
    }

    if(pGrafico == nullptr)
        pGrafico = this;
}   

Gerenciador_Grafico::~Gerenciador_Grafico() {
    if(window) {
        delete(window);
        window = nullptr;
    }
}

Gerenciador_Grafico* Gerenciador_Grafico::getGerenciadorGrafico() {
    if(pGrafico == nullptr) {
        pGrafico = new Gerenciador_Grafico();
    }   
    return pGrafico;
}

sf::RenderWindow* Gerenciador_Grafico::getWindow() {
    return window;
}

void Gerenciador_Grafico::limpaJanela() {
    window->clear();
}

void Gerenciador_Grafico::desenhaElemento(const sf::RectangleShape corpo) {
    window->draw(corpo);
}

void Gerenciador_Grafico::mostraElementos() {
    window->display();
}

void Gerenciador_Grafico::fecharJanela() {
    window->close();
}

bool Gerenciador_Grafico::verificaJanelaAberta() const {
    return window->isOpen();
}
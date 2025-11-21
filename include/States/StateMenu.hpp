#ifndef STATEMENU_HPP
#define STATEMENU_HPP
#include "Being.hpp"
#include "States/State.hpp"
#include <iostream>

namespace States{

class StateMenu : public State, public Being {

    private:
        int id;
        
    protected: 
        sf::RectangleShape background;
        sf::Texture bgTexture;
        sf::RenderWindow* window;
    public:
        StateMenu();
        ~StateMenu();

        void createNewWindow();
        void execute();


};

}
#endif
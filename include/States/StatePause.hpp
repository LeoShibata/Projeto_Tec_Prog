#ifndef STATEPAUSE_HPP
#define STATEPAUSE_HPP
#include "Being.hpp"
#include "States/State.hpp"

#include <iostream>

namespace States{

class StatePause : public State{

    private:
        int id;
        sf::Font font;
        sf::Text text;        
    public:
        StatePause();
        ~StatePause();
        //void keyPressed(const sf::Keyboard);
        
        void execute();
    


};

}
#endif
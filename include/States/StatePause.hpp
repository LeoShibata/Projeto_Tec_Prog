#ifndef STATEPAUSE_HPP
#define STATEPAUSE_HPP

#include "Being.hpp"
#include "States/State.hpp"
#include "Entities/Button.hpp"

#include <vector>

namespace States {
    class StatePause : public State {
        private:
            sf::Font font;
            sf::Text titleText; 
            sf::RectangleShape background;

            std::vector<Entities::Button*> buttons;
            int currentOption;
            sf::Clock inputClock;
            
            
        public:
            StatePause();
            ~StatePause();
            
            void draw() override;
            void execute();
    };
}

#endif
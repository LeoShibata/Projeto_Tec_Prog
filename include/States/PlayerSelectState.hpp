#ifndef PLAYERSELECTSTATE_HPP
#define PLAYERSELECT_HPP

#include "States/State.hpp"
#include "Entities/Button.hpp"
#include <vector>

namespace States {
    class PlayerSelectState : public State {    
        private:
            sf::Font font;
            sf::Text instructionText;
            sf::RectangleShape background;
            std::vector<Entities::Button*> buttons;
            int currentOption;
            sf::Clock inputClock;

            
        public:
            PlayerSelectState();
            ~PlayerSelectState();

            void draw() override;
            void execute() override;
    };
}

#endif 
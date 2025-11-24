#ifndef PLAYERSELECTSTATE_HPP
#define PLAYERSELECT_HPP

#include "States/State.hpp"
#include "Entities/Button.hpp"
#include <vector>

namespace States {
    class PlayerSelectState : public State {    
        private:
            std::vector<Entities::Button*> buttons;
            int currentOption;
            sf::Clock inputClock;
            sf::Text instructionText;
            sf::Font font;

            
        public:
            PlayerSelectState();
            ~PlayerSelectState();

            void draw() override;
            void execute() override;
    };
}

#endif 
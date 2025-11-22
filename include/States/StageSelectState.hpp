#ifndef STAGESELECTSTATE_HPP
#define STAGESELECTSTATE_HPP

#include "States/State.hpp"
#include "Entities/Button.hpp"
#include "SFML/Graphics.hpp"

#include <vector>

namespace States {
    class StageSelectState : public State {
        private:
            std::vector<Entities::Button*> buttons;
            int currentOption;
            sf::Clock inputClock;
            sf::Text titleText;
            sf::Font font;
        
        
        public:
            StageSelectState();
            ~StageSelectState();

            void execute() override;
            void draw() override;
    };
}


#endif
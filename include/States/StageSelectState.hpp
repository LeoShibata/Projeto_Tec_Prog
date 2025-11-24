#ifndef STAGESELECTSTATE_HPP
#define STAGESELECTSTATE_HPP

#include "States/State.hpp"
#include "Entities/Button.hpp"
#include "SFML/Graphics.hpp"

#include <vector>

namespace States {
    class StageSelectState : public State {
        private:
            sf::Font font;
            sf::Text titleText;
            sf::RectangleShape background;
            std::vector<Entities::Button*> buttons;
            int currentOption;
            sf::Clock inputClock;
        
        
        public:
            StageSelectState();
            ~StageSelectState();

            void draw() override;
            void execute() override;
    };
}


#endif
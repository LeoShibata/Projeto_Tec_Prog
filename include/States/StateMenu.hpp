#ifndef STATEMENU_HPP
#define STATEMENU_HPP

#include "States/State.hpp"
#include "Entities/Button.hpp"
#include <vector>

namespace States {
    class StateMenu : public State {
        private:
            sf::Font font;
            sf::Text titleText;
            
            sf::RectangleShape background;
            sf::Texture bgTexture;

            std::vector<Entities::Button*> buttons;
            int currentOption;
            sf::Clock inputClock;


        public:
            StateMenu();
            ~StateMenu();

            void draw() override;
            void execute() override;
    };
}

#endif
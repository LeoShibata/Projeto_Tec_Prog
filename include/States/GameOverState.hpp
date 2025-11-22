#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include "States/State.hpp"
#include "Entities/Button.hpp"

#include <vector>

namespace States {
    class GameOverState : public State {
        private:
            sf::Font font;
            sf::Text titleText;
            sf::RectangleShape background; 
            
            std::vector<Entities::Button*> buttons;
            int currentOption;
            sf::Clock inputClock;

        public:
            GameOverState();
            ~GameOverState();

            void execute() override;
            void draw() override;
    };
}

#endif
#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include "States/State.hpp"
#include "Entities/Button.hpp"
#include "Managers/LeaderboardManager.hpp"

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

            std::string playerName;
            sf::Text nameText;
            Managers::LeaderboardManager leaderboard;
            bool nameEntered;
            int finalScore;

        public:
            GameOverState();
            ~GameOverState();

            void execute() override;
            void draw() override;
    };
}

#endif
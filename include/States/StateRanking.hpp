#ifndef STATERANKING_HPP
#define STATERANKING_HPP

#include "States/State.hpp"
#include "Managers/LeaderboardManager.hpp" 

#include <vector>

namespace States {
    class StateRanking : public State {
        private:
            sf::Text titleText;
            sf::Font font;
            sf::RectangleShape background;
            Managers::LeaderboardManager leaderboard;
            std::vector<sf::Text> scoreTexts;

    
        public:
            StateRanking();
            ~StateRanking();

            void draw() override;
            void execute() override;
    };
}

#endif
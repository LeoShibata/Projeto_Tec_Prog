#ifndef STATERANKING_HPP
#define STATERANKING_HPP

#include "States/State.hpp"
#include "Managers/LeaderboardManager.hpp" 

#include <vector>

namespace States {
    class StateRanking : public State {
        private:
            sf::Font font;
            sf::Text titleText;
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
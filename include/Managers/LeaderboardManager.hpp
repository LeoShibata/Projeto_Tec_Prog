#ifndef LEADERBOARDMANAGER_HPP
#define LEADERBOARDMANAGER_HPP

#include "utils/json.hpp"

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace Managers {
    struct ScoreEntry {
        std::string name;
        int score;
    };

    class LeaderboardManager {
        private:
            std::vector<ScoreEntry> scores;
            const std::string filePath = "ranking.json";

        
        public:
            LeaderboardManager();
            ~LeaderboardManager();

            void addEntry(std::string name, int score);
            std::vector<ScoreEntry> getScores() const;

            void save();
            void load();
    };
}

#endif
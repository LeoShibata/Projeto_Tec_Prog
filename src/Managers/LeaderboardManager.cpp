#include "Managers/LeaderboardManager.hpp"

namespace Managers {

LeaderboardManager::LeaderboardManager() {
    load();
}


LeaderboardManager::~LeaderboardManager() { }


void LeaderboardManager::addEntry(std::string name, int score) {
    scores.push_back({name, score});

    // Ordena decrescente
    std::sort(scores.begin(), scores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
    });

    // top 5
    if(scores.size() > 5) {
        scores.resize(5);
    }

    save();
}


std::vector<ScoreEntry> LeaderboardManager::getScores() const {
    return scores;
}


void LeaderboardManager::save() {
    nlohmann::json j;

    for(size_t i = 0; i < scores.size(); i++) {
        const ScoreEntry& entry = scores[i];
        j.push_back({{"name", entry.name}, {"score", entry.score}});
    }

    std::ofstream o(filePath);
    o << std::setw(4) << j << std::endl;
    o.close();
}


void LeaderboardManager::load() {
    std::ifstream i(filePath);

    if(i.is_open()) {
        if(i.peek() == std::ifstream::traits_type::eof()) { // verifica se está vazio antes de tentar ler
            return;
        }

        try {
            nlohmann::json j;
            i >> j;

            scores.clear();

            for(size_t k = 0; k < j.size(); k++) {
                nlohmann::json& element = j[k];

                std::string name = element["name"];
                int score = element["score"];

                scores.push_back({name, score});
            }
        }
        catch(const nlohmann::json::parse_error& e) {
            std::cerr << "ERROR: Failed to read ranking.json" << e.what() << std::endl;
        }

        i.close();
    }
}

} // namespace Managers

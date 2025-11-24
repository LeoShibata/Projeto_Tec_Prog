#ifndef STATESPLAYING_HPP
#define STATESPLAYING_HPP

#include "States/State.hpp"
#include "Stages/Graveyard.hpp"
#include "Stages/Castle.hpp"

#include <queue>

namespace States {
    class StatePlaying: public State {
        public:
            static int playersCount;
            static Stages::Stage* pCurrentStage;
            
        private:
            std::queue<Stages::Stage*> stages;
            int idStage;
            sf::Clock inputClock;

            
        public:
            StatePlaying(int idStage); //ID system
            ~StatePlaying();
            
            void createStage();
            void loadStage();
            void execute();
    };
}

#endif
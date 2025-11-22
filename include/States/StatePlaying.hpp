#ifndef STATESPLAYING_HPP
#define STATESPLAYING_HPP

#include "States/State.hpp"
#include "Stages/Graveyard.hpp"
#include "Stages/Castle.hpp"

#include <queue>

namespace States {
    class StatePlaying: public State{
        public:
            static int playersCount;
            
        private:
            queue<Stages::Stage*> stages;
            int idStage;

            
        public:
            StatePlaying(int idStage); //ID system, 
            ~StatePlaying();
            void createStage();
            void loadStage();
            void execute();
            //void draw();
            //getAtualStage

            
    };
}

#endif
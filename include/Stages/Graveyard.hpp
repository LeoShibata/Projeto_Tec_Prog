#ifndef GRAVEYARD_HPP
#define GRAVEYARD_HPP  

#include "Stages/Stage.hpp"

#include "utils/json.hpp"

#include <fstream>

namespace Stages {
    class Graveyard : public Stage {
        protected:
            const int max_skeletons;

        protected:
            void createMap() override;
        
        public: 
            Graveyard();
            ~Graveyard();  
    };
} 

#endif
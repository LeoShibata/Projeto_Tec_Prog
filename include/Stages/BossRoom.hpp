#ifndef BOSSROOM_HPP
#define BOSSROOM_HPP  

#include "Stages/stage.hpp"

#include "utils/json.hpp"

#include <fstream>

namespace Stages {
    class BossRoom : public Stage {
        protected:
            const int max_boss;
        protected:
            void createMap() override;
        
        public: 
            BossRoom();
            ~BossRoom();

        
    };
} 

#endif
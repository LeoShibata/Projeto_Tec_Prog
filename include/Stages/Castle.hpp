#ifndef CASTLE_HPP
#define CASTLE_HPP  

#include "Stages/Stage.hpp"

#include "utils/json.hpp"

#include <fstream>

namespace Stages {
    class Castle : public Stage {
        protected:
            const int max_skeletons;

        protected:
            void createMap() override;
            void createSpike(sf::Vector2f pos);
            void createDeath(sf::Vector2f pos);
        
        public: 
            Castle();
            ~Castle();  
    };
} 

#endif
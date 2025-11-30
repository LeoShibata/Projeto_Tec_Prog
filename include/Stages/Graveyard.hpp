#ifndef GRAVEYARD_HPP
#define GRAVEYARD_HPP  

#include "Stages/Stage.hpp"
#include "utils/json.hpp"

#include <fstream>

namespace Stages {
    class Graveyard : public Stage {
        protected:
            const int max_skeletons;
            const int max_mudhand;

            
        protected:
            void createMap() override;
            void createMudHand(sf::Vector2f pos);
            void createBat(sf::Vector2f pos);
        
        public: 
            Graveyard();
            ~Graveyard();  
    };
} 

#endif
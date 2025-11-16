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
        
        public: 
            Castle();
            ~Castle();  
    };
} 

#endif
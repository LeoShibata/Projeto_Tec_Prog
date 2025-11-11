#ifndef STAGE1_HPP
#define STAGE1_HPP  

#include "Stages/stage.hpp"

#include "utils/json.hpp"

#include <fstream>

namespace Stages {
    class Stage1 : public Stage {
        protected:
            const int max_skeletons;
        protected:
            void createMap() override;
        
        public: 
            Stage1();
            ~Stage1();

        
    };
} 

#endif
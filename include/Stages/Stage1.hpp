#ifndef STAGE1_HPP
#define STAGE1_HPP  

#include "Stages/Stage.hpp"

#include "utils/json.hpp"

#include <fstream>

namespace Stages {
    class Stage1 : public Stage {
        public: 
            Stage1();
            ~Stage1();

        protected:
            void createMap() override;
    };
} 

#endif
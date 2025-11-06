#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "Entities/Obstacles/Obstacle.hpp"

namespace Entities::Obstacles {
    class Platform : public Obstacle {
        private:
            int height;

        public:
            Platform();
            ~Platform();

            void execute() override;
            void obstaculizar(Player* pPlayer) override;
    };
}

#endif
#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

namespace Entities::Obstacles {
    class Player;
    class Obstacle {
        protected:
            bool danoso;

        public:
            Obstacle();
            ~Obstacle();

            virtual void execute() = 0;
            virtual void obstaculizar(Player* pPlayer) = 0;
    };
}

#endif
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Being.hpp"

namespace Entities {
    namespace IDs {
        enum IDs {
            player,
            enemy,
            obstacles,
            plataform
        };
    }

    class Entity : public Being {
        protected:
            //sf::Vector2f position;
            sf::Vector2f velocity;
            float speed_mod;
            //buffer ostream

        protected:
            void setSpeedmod(float spd);
            void setVelocity(sf::Vector2f vel);

        public:
            Entity(float speed, sf::Vector2f position, sf::Vector2f size);
            virtual ~Entity();
            float getSpeedmod();
            virtual void update() = 0;
            sf::Vector2f getVelocity();
            virtual void collision(Entity* other) = 0;
    };
}

#endif
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Being.hpp"

namespace Entities {
    namespace IDs {
        enum IDs {
            empty = 0,
            player,
            enemy,
            obstacle,
            platform,
            floor,
            projectile
        };
    }

    class Entity : public Being {
        protected:
            IDs::IDs typeId;
            sf::Vector2f velocity;
            float speed_mod;
            bool isAlive;

        protected:
            void setSpeedmod(float spd);
            
        public:
            Entity(sf::Vector2f position, sf::Vector2f size, float speed);
            virtual ~Entity();
            
            float getSpeedmod();
            sf::Vector2f getVelocity();
            void setVelocity(sf::Vector2f vel);
            virtual IDs::IDs getTypeId() const;
            virtual bool getIsAlive() const;
            
            virtual void update() = 0;
            virtual void collision(Entity* other, float over, int collisionType) = 0;
    };
}

#endif

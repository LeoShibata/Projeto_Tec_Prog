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
            platform
        };
    }

    class Entity : public Being {
        protected:
            IDs::IDs typeId;
            sf::Vector2f velocity;
            float speed_mod;

        protected:
            void setSpeedmod(float spd);
            void setVelocity(sf::Vector2f vel);

        public:
            Entity(sf::Vector2f position, sf::Vector2f size, float speed);
            virtual ~Entity();
            
            float getSpeedmod();
            sf::Vector2f getVelocity();
            virtual IDs::IDs getTypeId() const;
            
            virtual void update() = 0;
            virtual void collision(Entity* other, sf::Vector2f ds = sf::Vector2f(0.f, 0.f)) = 0;
    };
}

#endif

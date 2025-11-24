#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Being.hpp"
#include "utils/json.hpp"

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

            sf::Clock clock;
            float dt;

            bool onGround;
            static const float GRAVITY;


        protected:
            nlohmann::json saveEntityState() const; // método auxiliar para salvar dados comuns de todas entidades(pos, vel, id)
            void setSpeedmod(float spd);
            
        public:
            Entity(sf::Vector2f position, sf::Vector2f size, float speed);
            virtual ~Entity();
            
            void applyGravity();
            void updateDt();
            void setVelocity(sf::Vector2f vel);
            sf::Vector2f getVelocity();
            float getSpeedmod();
            void setOnGround(bool ground);
            bool getOnGround() const;
            virtual IDs::IDs getTypeId() const;
            virtual bool getIsAlive() const;

            void loadEntityState(const nlohmann::json& j); // método para carregar estado básico
            
            virtual void update() = 0;
            virtual void collision(Entity* other, float over, int collisionType) = 0;
            virtual nlohmann::json save() = 0;
    };
}

#endif

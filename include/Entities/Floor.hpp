#ifndef FLOOR_HPP
#define FLOOR_HPP

#include "Entities/Entity.hpp"

namespace Characters {
    class Player;
    class Enemy;
}

namespace Entities {
    class Floor : public Entity {
        private:
            sf::Texture texture;

        public:
            Floor(sf::Vector2f position, sf::Vector2f size);
            ~Floor();

            void collision(Entity* other, float ds, int collisionType) override;

            void update() override;
            void execute() override;

            nlohmann::json save() override;
    };
}

#endif
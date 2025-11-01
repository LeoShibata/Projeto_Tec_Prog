#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP

#include <List/EntityList.hpp>

#include <SFML/Graphics.hpp>
#include <cmath>

namespace Managers {
    class CollisionManager {
        private:
            List::EntityList* characterList;
            List::EntityList* obstacleList;

        public:
            CollisionManager(List::EntityList* characterList, List::EntityList* obstacleList);
            ~CollisionManager();
            const sf::Vector2f collisionDetection(Entities::Entity* ent1, Entities::Entity* ent2);
            void run();
    };
}

#endif
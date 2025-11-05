#ifndef ENTITYLIST_HPP 
#define ENTITYLIST_HPP

#include <List/List.hpp>
#include <Entities/Entity.hpp>

namespace List {
    class EntityList {
        private:
            List<Entities::Entity> objEntityList;
        
        public:
            EntityList();
            ~EntityList();
            
            void addEntity(Entities::Entity* entity);
            void removeEntity(Entities::Entity* entity);
            void removeEntity(int pos);
            int getSize();
            Entities::Entity* operator[](int pos);
            void executeAll();
            void drawAll(sf::RenderWindow* window);
    };
}

#endif
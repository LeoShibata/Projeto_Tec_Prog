#include <List/EntityList.hpp>

namespace List {

EntityList::EntityList() :
    objEntityList()
{

}


EntityList::~EntityList() { }


void EntityList::addEntity(Entities::Entity* entity) {
    objEntityList.addElement(entity);
}


void EntityList::removeEntity(Entities::Entity* entity) {
    objEntityList.removeElement(entity);
}


void EntityList::removeEntity(int pos) {
    objEntityList.removeElement(pos);
}


int EntityList::getSize() {
    return objEntityList.getSize();
}


Entities::Entity* EntityList::operator[](int pos) {
    return objEntityList.operator[](pos);
}


void EntityList::executeAll() {
    int size = objEntityList.getSize();
    Entities::Entity* aux = nullptr;
    for(int i = 0; i < size; i++) {
        aux = objEntityList.operator[](i);
        aux->execute();
    }
}


void EntityList::drawAll(sf::RenderWindow* window) {
    int size = objEntityList.getSize();
    Entities::Entity* aux = nullptr;
    for(int i = 0; i < size; i++) {
        aux = objEntityList.operator[](i);
        window->draw(aux->getBody());
    }
}

}
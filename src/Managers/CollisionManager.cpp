#include "Managers/CollisionManager.hpp"
#include <Entities/Entity.hpp>

namespace Managers {

CollisionManager::CollisionManager(List::EntityList* characterList, List::EntityList* obstacleList) :
    characterList(characterList), 
    obstacleList(obstacleList)
{ 

}

CollisionManager::~CollisionManager() { }

const sf::Vector2f CollisionManager::collisionDetection(Entities::Entity* ent1, Entities::Entity* ent2) {
    sf::Vector2f pos1 = ent1->getPos();
    sf::Vector2f pos2 = ent2->getPos();

    sf::Vector2f size1 = ent1->getSize();
    sf::Vector2f size2 = ent2->getSize();

    sf::Vector2f distanceBetweenCenters(
        fabs((pos1.x + size1.x/2.f) - (pos2.x + size2.x/2.f)),
        fabs((pos1.y + size1.y/2.f) - (pos2.y + size2.y/2.f))
    );
    sf::Vector2f sumHalfRectangle(size1.x/2.f + size2.x/2.f, size1.y/2.f + size2.y/2.f);
    return sf::Vector2f(
        distanceBetweenCenters.x - sumHalfRectangle.x,
        distanceBetweenCenters.y - sumHalfRectangle.y
    );
}

void CollisionManager::run() {
    // character vs character
    for(int i = 0; i < characterList->getSize() - 1; i++) {
        Entities::Entity* ent1 = characterList->operator[](i);
        for(int j = i + 1; j < characterList->getSize(); j++) {
            Entities::Entity* ent2 = characterList->operator[](j);
            sf::Vector2f ds = collisionDetection(ent1, ent2); 
            if(ds.x < 0.f && ds.y < 0.f) {
                ent1->collision(ent2, ds);
                ent2->collision(ent1, ds);
            }
        }
    }

    // character vs obstacle
    for(int i = 0; i < characterList->getSize(); i++) {
        Entities::Entity* ent1 = characterList->operator[](i);
        for(int j = 0; j < obstacleList->getSize(); j++) {
            Entities::Entity* ent2 = obstacleList->operator[](j);
            sf::Vector2f ds = collisionDetection(ent1, ent2); 
            if(ds.x < 0.f && ds.y < 0.f) {
                ent2->collision(ent1, ds);
            }
        }
    }
}

}
#include "Managers/CollisionManager.hpp"
#include <Entities/Entity.hpp>

namespace Managers {

CollisionManager::CollisionManager() : pPlayer(NULL)
{ 
    cout << "init colisao" << endl;

}

CollisionManager::~CollisionManager() { }

void CollisionManager::setPlayer(Entities::Characters::Player* pPlayer){
    this->pPlayer = pPlayer;
    cout << "player!" << endl;

}


void CollisionManager::includeEntity(Entities::Entity* ent1){
    cout << ent1->getTypeId() << endl;

    switch (ent1->getTypeId())
    {
    case 0:
        //try catch
        cout << "chamou mas add nada" << endl;
        break;
    case (Entities::IDs::player):
        this->pPlayer = static_cast<Entities::Characters::Player*> (ent1);
        break;
    case (Entities::IDs::enemy):
        lIs.push_back(static_cast<Entities::Characters::Enemies*> (ent1));
        cout << "botou" << endl;
        break;
    case (Entities::IDs::obstacle):
        lOs.push_back(static_cast<Entities::Obstacles::Obstacle*> (ent1));
                        cout << "add obstaculo" << endl;

        break;
    default:

        break;
    }
}

void CollisionManager::removeEntity(Entities::Entity* ent1){
    switch (ent1->getTypeId())
    {
    case 0:
        //try catch
        break;
    case (Entities::IDs::player):
        this->pPlayer = NULL;
        break;
    case (Entities::IDs::enemy):
        lIs.erase(std::remove(lIs.begin(), lIs.end(), static_cast<Entities::Characters::Enemies*> (ent1)), lIs.end());
        break;
    case (Entities::IDs::obstacle):
    
        break;

    default:

        break;
    }
}

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

void CollisionManager::verifyPlayerEnemy(){
    for (int i = 0; i< lIs.size(); i++){
        sf::Vector2f ds = collisionDetection(static_cast<Entities::Entity*>(lIs[i]), static_cast<Entities::Entity*> (pPlayer));
        if(ds.x < 0.f && ds.y < 0.f){
            pPlayer->collision(lIs[i], ds);
        }
            

    }
    
}

void CollisionManager::verifyPlayerObstacle(){
    for (list<Entities::Obstacles::Obstacle*>::iterator it = lOs.begin(); it != lOs.end(); ++it) {
        sf::Vector2f ds = collisionDetection(static_cast<Entities::Entity*>(*it), static_cast<Entities::Entity*> (pPlayer));
        if(ds.x < 0.f && ds.y < 0.f){
            (*it)->collision(pPlayer, ds);//search more after
            pPlayer->collision(*it, ds);
        }
    
    }
    
}

void CollisionManager::run() {
    // character vs character
    verifyPlayerEnemy();
    /*for(int i = 0; i < characterList->getSize() - 1; i++) {
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
    */
    verifyPlayerObstacle();
    /*
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
        */
}

}
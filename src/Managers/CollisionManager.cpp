#include "Managers/CollisionManager.hpp"
#include <Entities/Entity.hpp>

using namespace std;
namespace Managers {

CollisionManager::CollisionManager() : 
    pPlayer(NULL)
{ 

}

CollisionManager::~CollisionManager() { }

void CollisionManager::setPlayer(Entities::Characters::Player* pPlayer) {
    this->pPlayer = pPlayer;
}

void CollisionManager::includeEntity(Entities::Entity* ent1) {
    switch (ent1->getTypeId()) {
        case(Entities::IDs::empty) :
            //try catch
            break;
        case(Entities::IDs::player) :
            this->pPlayer = static_cast<Entities::Characters::Player*> (ent1);
            break;
        case(Entities::IDs::enemy) :
            lIs.push_back(static_cast<Entities::Characters::Enemies*> (ent1));
            break;
        case(Entities::IDs::obstacle) :
            lOs.push_back(static_cast<Entities::Obstacles::Obstacle*> (ent1));
            break;
        
        default:
            break;
    }
}

void CollisionManager::removeEntity(Entities::Entity* ent1){
    switch (ent1->getTypeId()) {
        case(Entities::IDs::empty) :
            //try catch
            break;
        case (Entities::IDs::player) :
            this->pPlayer = NULL;
            break;
        case (Entities::IDs::enemy) :
            lIs.erase(std::remove(lIs.begin(), lIs.end(), static_cast<Entities::Characters::Enemies*> (ent1)), lIs.end());
            break;
        case (Entities::IDs::obstacle) :
            lOs.erase(std::remove(lOs.begin(), lOs.end(), static_cast<Entities::Obstacles::Obstacle*> (ent1)), lOs.end());
            break;

        default:
            break;
    }
}

const CollisionManager::CollisionData CollisionManager::collisionDetection(Entities::Entity* ent1, Entities::Entity* ent2) {

   
    sf::Vector2f pos1 = ent1->getPos();
    sf::Vector2f pos2 = ent2->getPos();

    sf::Vector2f size1 = ent1->getSize();
    sf::Vector2f size2 = ent2->getSize();

    CollisionData cData;
    sf::Vector2f distanceBetweenCenters(
        fabs((pos1.x + size1.x/2.f) - (pos2.x + size2.x/2.f)),
        fabs((pos1.y + size1.y/2.f) - (pos2.y + size2.y/2.f))
    );
    sf::Vector2f sumHalfRectangle(size1.x/2.f + size2.x/2.f, size1.y/2.f + size2.y/2.f);
    
    float overX = distanceBetweenCenters.x - sumHalfRectangle.x;
    float overY = distanceBetweenCenters.y - sumHalfRectangle.y;
    
    if( overX <0 && overY <0){
        cData.collided = true;

    if(overX > overY){
        if((pos2.x - pos1.x) > 0)
            overX *= -1;
        cData.ds = overX;
        cData.type = CollisionType::Horizontal;
    }else{
        if((pos2.y - pos1.y) > 0)
            overY *= -1;
        cData.ds = overY;
        cData.type = CollisionType::Vertical;
        }
        
    }
    return cData;   
}

void CollisionManager::verifyPlayerEnemy() {
    for(int i = 0; i < lIs.size(); i++) {
        CollisionData data = collisionDetection(static_cast<Entities::Entity*>(lIs[i]), static_cast<Entities::Entity*> (pPlayer));
        if(data.collided == true) {
            pPlayer->collision(lIs[i], data.ds, int(data.type));
        }
    }
}

void CollisionManager::verifyPlayerObstacle() {
    for(list<Entities::Obstacles::Obstacle*>::iterator it = lOs.begin(); it != lOs.end(); ++it) {
        CollisionData data  = collisionDetection(static_cast<Entities::Entity*>(*it), static_cast<Entities::Entity*> (pPlayer));
        if(data.collided == true) {
            cout <<data.ds << " colisao player  inimigo " <<data.collided << endl;

            (*it)->collision(pPlayer, data.ds, int(data.type)); // search more after
            pPlayer->collision(*it, data.ds, int(data.type));
        }
    } 
}

void CollisionManager::verifyEnemyObstacle() {
    for(int i = 0; i < lIs.size(); i++) {
        for(list<Entities::Obstacles::Obstacle*>::iterator it = lOs.begin(); it != lOs.end(); ++it) {
            CollisionData data  = collisionDetection(static_cast<Entities::Entity*>(lIs[i]), static_cast<Entities::Entity*>(*it));
            if(data.collided == true) {
                cout <<data.ds << " enemy obstacle  " <<data.collided << endl;

                lIs[i]->collision(*it, data.ds, int(data.type));
                (*it)->collision(lIs[i], data.ds, int(data.type));
                
            }
        }
    }
}

void CollisionManager::run() {
    verifyPlayerEnemy();
    verifyPlayerObstacle();
    verifyEnemyObstacle();
}

}
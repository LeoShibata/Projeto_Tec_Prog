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
        case(Entities::IDs::projectile) :
            lPs.insert(static_cast<Entities::Projectile*> (ent1));
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
        case(Entities::IDs::projectile) :
            lPs.erase(static_cast<Entities::Projectile*> (ent1));
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
    CollisionData data;
    for(int i = 0; i < lIs.size(); i++) {
        data = collisionDetection(static_cast<Entities::Entity*>(lIs[i]), static_cast<Entities::Entity*> (pPlayer));
        if(data.collided == true) {
            pPlayer->collision(lIs[i], data.ds, int(data.type));

        }
    }
}

void CollisionManager::verifyPlayerObstacle() {
    CollisionData data;
    for(list<Entities::Obstacles::Obstacle*>::iterator it = lOs.begin(); it != lOs.end(); ++it) {
        data  = collisionDetection(static_cast<Entities::Entity*>(*it), static_cast<Entities::Entity*> (pPlayer));
        if(data.collided == true) {

            (*it)->collision(pPlayer, data.ds, int(data.type)); // search more after
            pPlayer->collision(*it, data.ds, int(data.type));
        }
    } 
}

void CollisionManager::verifyEnemyObstacle() {
    CollisionData data;
    for(int i = 0; i < lIs.size(); i++) {
        for(list<Entities::Obstacles::Obstacle*>::iterator it = lOs.begin(); it != lOs.end(); ++it) {
            data  = collisionDetection(static_cast<Entities::Entity*>(lIs[i]), static_cast<Entities::Entity*>(*it));
            if(data.collided == true) {

                lIs[i]->collision(*it, data.ds, int(data.type));
                (*it)->collision(lIs[i], data.ds, int(data.type));
                
            }
        }
    }
}

void CollisionManager::verifyProjecObstacle() {
    CollisionData data;
    for(set<Entities::Projectile*>::iterator its = lPs.begin(); its != lPs.end(); ++its) {
        for(list<Entities::Obstacles::Obstacle*>::iterator itl = lOs.begin(); itl != lOs.end(); ++itl) {
            data  = collisionDetection(static_cast<Entities::Entity*>(*its), static_cast<Entities::Entity*>(*itl));
            if(data.collided == true) {
                cout<<"collded"<<endl;
                (*its)->collision(*itl, data.ds, int(data.type));
                //(*itl)->collision(*its, data.ds, int(data.type));
                
            }
        }
    }
}

void CollisionManager::verifyProjecEnemies() {
    CollisionData data;
    for(set<Entities::Projectile*>::iterator its = lPs.begin(); its != lPs.end(); ++its) {
        for(int i = 0; i < lIs.size(); i++) {
            data  = collisionDetection(static_cast<Entities::Entity*>(*its), static_cast<Entities::Entity*>(lIs[i]));
            if(data.collided == true) {
                cout<<"collded"<<endl;
                (*its)->collision(lIs[i], data.ds, int(data.type));
                //(*itl)->collision(*its, data.ds, int(data.type));
                
            }
        }
    }
}
void CollisionManager::verifyProjectPlayers() {
    CollisionData data;
    for(set<Entities::Projectile*>::iterator its = lPs.begin(); its != lPs.end(); ++its) {
        data  = collisionDetection(static_cast<Entities::Entity*>(*its), static_cast<Entities::Entity*> (pPlayer));            if(data.collided == true) {
            cout<<"collded"<<endl;
            (*its)->collision(pPlayer, data.ds, int(data.type));
            //(*itl)->collision(*its, data.ds, int(data.type));
                
        }
    }
}

void CollisionManager::run() {
    verifyPlayerEnemy();
    verifyPlayerObstacle();
    verifyEnemyObstacle();
    verifyProjecObstacle();
    verifyProjecEnemies();
    verifyProjectPlayers();
}

}
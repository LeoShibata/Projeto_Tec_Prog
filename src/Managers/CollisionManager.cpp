#include "Managers/CollisionManager.hpp"
#include <Entities/Entity.hpp>

using namespace std;

namespace Managers {

CollisionManager::CollisionManager() : 
    pPlayer1(nullptr),
    pPlayer2(nullptr)
{ 

}


CollisionManager::~CollisionManager() { }


void CollisionManager::setPlayer1(Entities::Characters::Player* pPlayer) {
    this->pPlayer1 = pPlayer;
}


void CollisionManager::setPlayer2(Entities::Characters::Player* pPlayer) {
    this->pPlayer2 = pPlayer;
}


void CollisionManager::includeEntity(Entities::Entity* ent1) {
    switch (ent1->getTypeId()) {
        case(Entities::IDs::empty) :
            //try catch
            break;
        case(Entities::IDs::player) :
            break;
        case(Entities::IDs::enemy) :
            lIs.push_back(static_cast<Entities::Characters::Enemies*> (ent1));
            break;
        case(Entities::IDs::floor) : 
            lFs.push_back(static_cast<Entities::Floor*>(ent1));
            break;
        case(Entities::IDs::obstacle) :
            lOs.push_back(static_cast<Entities::Obstacles::Obstacle*> (ent1));
            break;
        case(Entities::IDs::platform) :
            lOs.push_back(static_cast<Entities::Obstacles::Obstacle*> (ent1));
            break;
        case(Entities::IDs::projectile) :
            lPs.insert(static_cast<Entities::Projectile*> (ent1));
            cout<<"added projectil" <<endl;
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
        case(Entities::IDs::player) :
            if(static_cast<Entities::Entity*>(pPlayer1) == ent1) {
                pPlayer1 = NULL;
            }
            if(static_cast<Entities::Entity*>(pPlayer2) == ent1) {
                pPlayer2 = NULL;
            }
            break;
        case(Entities::IDs::enemy) :
            lIs.erase(std::remove(lIs.begin(), lIs.end(), static_cast<Entities::Characters::Enemies*> (ent1)), lIs.end());
            break;
        case(Entities::IDs::floor) :
            lFs.erase(std::remove(lFs.begin(), lFs.end(), static_cast<Entities::Floor*>(ent1)), lFs.end());
            break;
        case(Entities::IDs::obstacle) :
            lOs.erase(std::remove(lOs.begin(), lOs.end(), static_cast<Entities::Obstacles::Obstacle*> (ent1)), lOs.end());
            break;
        case(Entities::IDs::platform) :
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
    sf::Vector2f distanceBetweenCenters (
        fabs((pos1.x + size1.x/2.f) - (pos2.x + size2.x/2.f)),
        fabs((pos1.y + size1.y/2.f) - (pos2.y + size2.y/2.f))
    );
    sf::Vector2f sumHalfRectangle(size1.x/2.f + size2.x/2.f, size1.y/2.f + size2.y/2.f);
    
    float overX = distanceBetweenCenters.x - sumHalfRectangle.x;
    float overY = distanceBetweenCenters.y - sumHalfRectangle.y;
    
    if(overX < 0 && overY < 0){
        cData.collided = true;

        if(overX > overY){
            if((pos2.x - pos1.x) > 0) {
                overX *= -1;
            }
            cData.ds = overX;
            cData.type = CollisionType::Horizontal;
        } else {
            if((pos2.y - pos1.y) > 0) {
                overY *= -1;
            }
            cData.ds = overY;
            cData.type = CollisionType::Vertical;
        }
    }
    
    return cData;   
}


void CollisionManager::verifyPlayerEnemy() {
    CollisionData data;
    for(int i = 0; i < lIs.size(); i++) {
        if(pPlayer1 && pPlayer1->getIsAlive()) { 
            data = collisionDetection(static_cast<Entities::Entity*>(lIs[i]), static_cast<Entities::Entity*> (pPlayer1));
            if(data.collided == true) {
                pPlayer1->collision(lIs[i], data.ds, int(data.type));
            }
        }
        if(pPlayer2 && pPlayer2->getIsAlive()) { 
            data = collisionDetection(static_cast<Entities::Entity*>(lIs[i]), static_cast<Entities::Entity*> (pPlayer2));
            if(data.collided == true) {
                pPlayer2->collision(lIs[i], data.ds, int(data.type));
            }
        }
    }
}


// -------------- Floor --------------
void CollisionManager::verifyPlayerFloor() {
    CollisionData data;
    list<Entities::Floor*>::iterator it;
    for(it = lFs.begin(); it != lFs.end(); ++it) {
        Entities::Floor* pFloor = *it; 
        if(pPlayer1 && pPlayer1->getIsAlive()) { 
            data = collisionDetection(static_cast<Entities::Entity*>(pFloor), static_cast<Entities::Entity*>(pPlayer1));
            if(data.collided) {
                pFloor->collision(pPlayer1, data.ds, int(data.type));
            }
        }
        if(pPlayer2 && pPlayer2->getIsAlive()) { 
            data = collisionDetection(static_cast<Entities::Entity*>(pFloor), static_cast<Entities::Entity*>(pPlayer2));
            if(data.collided) {
                pFloor->collision(pPlayer2, data.ds, int(data.type));
            }
        }
    } 
}


void CollisionManager::verifyEnemyFloor() {
    CollisionData data;
    for(int i = 0; i < lIs.size(); i++) {
        list<Entities::Floor*>::iterator it;
        for(it = lFs.begin(); it != lFs.end(); ++it) {
            Entities::Floor* pFloor = *it;
            if(lIs[i]->getIsAlive()) { 
                data = collisionDetection(static_cast<Entities::Entity*>(lIs[i]), static_cast<Entities::Entity*>(pFloor));
                if(data.collided) {
                    pFloor->collision(lIs[i], data.ds, int(data.type));
                }
            }
        }
    }
}


// -------------- Obstacle --------------
void CollisionManager::verifyPlayerObstacle() {
    CollisionData data;
    for(list<Entities::Obstacles::Obstacle*>::iterator it = lOs.begin(); it != lOs.end(); ++it) {
        if(pPlayer1 && pPlayer1->getIsAlive()) { 
            data  = collisionDetection(static_cast<Entities::Entity*>(*it), static_cast<Entities::Entity*> (pPlayer1));
            if(data.collided == true) {
                (*it)->collision(pPlayer1, data.ds, int(data.type)); // search more after
                pPlayer1->collision(*it, data.ds, int(data.type));
            }
        }
        if(pPlayer2 && pPlayer2->getIsAlive()) { 
            data  = collisionDetection(static_cast<Entities::Entity*>(*it), static_cast<Entities::Entity*> (pPlayer2));
            if(data.collided == true) {
                (*it)->collision(pPlayer2, data.ds, int(data.type)); // search more after
                pPlayer2->collision(*it, data.ds, int(data.type));
            }
        }
    } 
}


void CollisionManager::verifyEnemyObstacle() {
    CollisionData data;
    for(int i = 0; i < lIs.size(); i++) {
        for(list<Entities::Obstacles::Obstacle*>::iterator it = lOs.begin(); it != lOs.end(); ++it) {
            if(pPlayer1 && pPlayer1->getIsAlive()) { 
                data  = collisionDetection(static_cast<Entities::Entity*>(lIs[i]), static_cast<Entities::Entity*>(*it));
                if(data.collided == true) {
                    lIs[i]->collision(*it, data.ds, int(data.type));
                    (*it)->collision(lIs[i], data.ds, int(data.type));
                }
            }
            if(pPlayer2 && pPlayer2->getIsAlive()) { 
                data  = collisionDetection(static_cast<Entities::Entity*>(lIs[i]), static_cast<Entities::Entity*>(*it));
                if(data.collided == true) {
                    lIs[i]->collision(*it, data.ds, int(data.type));
                    (*it)->collision(lIs[i], data.ds, int(data.type));
                }
            }
        }
    }
}


// -------------- Projectile --------------
void CollisionManager::verifyProjectObstacle() {
    CollisionData data;
    for(set<Entities::Projectile*>::iterator its = lPs.begin(); its != lPs.end(); ++its) {
        for(list<Entities::Obstacles::Obstacle*>::iterator itl = lOs.begin(); itl != lOs.end(); ++itl) {
            if(pPlayer1 && pPlayer1->getIsAlive()) { 
                data  = collisionDetection(static_cast<Entities::Entity*>(*its), static_cast<Entities::Entity*>(*itl));
                if(data.collided == true) {
                    cout<<"collded"<<endl;
                    (*its)->collision(*itl, data.ds, int(data.type));
                    //(*itl)->collision(*its, data.ds, int(data.type));
                }
            }
            if(pPlayer2 && pPlayer2->getIsAlive()) { 
                data  = collisionDetection(static_cast<Entities::Entity*>(*its), static_cast<Entities::Entity*>(*itl));
                if(data.collided == true) {
                    cout<<"collded"<<endl;
                    (*its)->collision(*itl, data.ds, int(data.type));
                    //(*itl)->collision(*its, data.ds, int(data.type));
                }
            }
        }
    }
}


void CollisionManager::verifyProjectFloor() {
    CollisionData data;
    for(std::set<Entities::Projectile*>::iterator itP = lPs.begin(); itP != lPs.end(); ++itP) {
        Entities::Projectile* pProjectile = *itP;
        std::list<Entities::Floor*>::iterator itF;
        for(itF = lFs.begin(); itF != lFs.end(); ++itF) {
            Entities::Floor* pFloor = *itF;
            data = collisionDetection(static_cast<Entities::Entity*>(pProjectile), static_cast<Entities::Entity*>(pFloor));
            if(data.collided) {
                pProjectile->collision(static_cast<Entities::Entity*>(pFloor), data.ds, int(data.type));
                break; 
            }
        }
    }
}


void CollisionManager::verifyProjectEnemies() {
    CollisionData data;
    for(set<Entities::Projectile*>::iterator its = lPs.begin(); its != lPs.end(); ++its) {
        for(int i = 0; i < lIs.size(); i++) {
            if(pPlayer1 && pPlayer1->getIsAlive()) { 
                data  = collisionDetection(static_cast<Entities::Entity*>(*its), static_cast<Entities::Entity*>(lIs[i]));
                if(data.collided == true) {
                    cout<<"collded"<<endl;
                    (*its)->collision(lIs[i], data.ds, int(data.type));
                    //(*itl)->collision(*its, data.ds, int(data.type));
                    
                }
            }
            if(pPlayer2 && pPlayer2->getIsAlive()) { 
                data  = collisionDetection(static_cast<Entities::Entity*>(*its), static_cast<Entities::Entity*>(lIs[i]));
                if(data.collided == true) {
                    cout<<"collded"<<endl;
                    (*its)->collision(lIs[i], data.ds, int(data.type));
                    //(*itl)->collision(*its, data.ds, int(data.type));
                    
                }
            }
        }
    }
}


void CollisionManager::verifyProjectPlayers() {
    CollisionData data;
    for(set<Entities::Projectile*>::iterator its = lPs.begin(); its != lPs.end(); ++its) {
        if(pPlayer1 && pPlayer1->getIsAlive()) { 
            data  = collisionDetection(static_cast<Entities::Entity*>(*its), static_cast<Entities::Entity*> (pPlayer1));            
            if(data.collided == true) {
                cout<<"collded"<<endl;
                (*its)->collision(pPlayer1, data.ds, int(data.type));
                //(*itl)->collision(*its, data.ds, int(data.type));      
            }
        }
        if(pPlayer2 && pPlayer2->getIsAlive()) { 
            data  = collisionDetection(static_cast<Entities::Entity*>(*its), static_cast<Entities::Entity*> (pPlayer2));            
            if(data.collided == true) {
                cout<<"collded"<<endl;
                (*its)->collision(pPlayer2, data.ds, int(data.type));
                //(*itl)->collision(*its, data.ds, int(data.type));  
            }
        }
    }
}


void CollisionManager::run() {
    verifyPlayerEnemy();
    verifyPlayerFloor();
    verifyEnemyFloor();     
    verifyPlayerObstacle();
    verifyEnemyObstacle();
    verifyProjectObstacle();
    verifyProjectFloor();
    verifyProjectEnemies();
    verifyProjectPlayers();
}

}
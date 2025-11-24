#include "Stages/Stage.hpp"
#include "Entities/Characters/Player.hpp"
#include "Managers/StateManager.hpp"

#include <iostream>

using json = nlohmann::json;
using namespace std;

namespace Stages {

Stage::Stage() : 
    Being(sf::Vector2f(0,0)),
    pEvent(Managers::EventManager::getEventManager()),
    pGraphic(Managers::GraphicManager::getGraphicManager()),
    pCollision(nullptr), pPlayer1(nullptr), pPlayer2(nullptr),
    characterList(new List::EntityList()),
    obstacleList(new List::EntityList()),
    structureList(new List::EntityList()),
    projectileList(new List::EntityList()),
    hpBar1(nullptr), hpBar2(nullptr),
    max_bats(20), max_obstacles(12), 
    gameOver(false)
{ 
    pCollision = new Managers::CollisionManager();
    Entities::Characters::Enemies::clearPlayers(); // limpa jogadores estáticos de enemies
}


Stage::~Stage() {
    if(pGraphic) {
        pGraphic->setPlayer1(nullptr);   
        pGraphic->setPlayer2(nullptr);   
    }

    if(pCollision) {
        delete pCollision;
        pCollision = nullptr;
    }
    if(characterList) {
        delete characterList;
        characterList = nullptr;
    }
    if(obstacleList) {
        delete obstacleList;
        obstacleList = nullptr;
    }
    if(hpBar1) {
        delete hpBar1;
    }
    if(hpBar2) {
        delete hpBar2;
    }
}


// ----------------- Players -----------------
void Stage::createPlayer1(sf::Vector2f pos) {
    pPlayer1 = new Entities::Characters::Player(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize), 1);
    pPlayer1->setStage(static_cast<Stage*>(this));// please work
    characterList->addEntity(pPlayer1);

    pCollision->setPlayer1(pPlayer1);
    pEvent->setPlayer1(pPlayer1);
    Entities::Characters::Enemies::setPlayer1(pPlayer1);
    Entities::Obstacles::Obstacle::setPlayer1(pPlayer1);
    pGraphic->setPlayer1(pPlayer1);

    hpBar1 = new Entities::HealthBar(sf::Vector2f(20.f, 20.f), sf::Vector2f(200.f, 20.f), sf::Color::Red, pPlayer1);
}


void Stage::createPlayer2(sf::Vector2f pos) {
    pPlayer2 = new Entities::Characters::Player(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize), 2);
    pPlayer2->setStage(static_cast<Stage*>(this));// please work
    characterList->addEntity(pPlayer2);

    pCollision->setPlayer2(pPlayer2);
    pEvent->setPlayer2(pPlayer2);
    Entities::Characters::Enemies::setPlayer2(pPlayer2);
    Entities::Obstacles::Obstacle::setPlayer2(pPlayer2);
    pGraphic->setPlayer2(pPlayer2);

    hpBar2 = new Entities::HealthBar(sf::Vector2f(1060.f, 20.f), sf::Vector2f(200.f, 20.f), sf::Color::Blue, pPlayer2);
}


// ----------------- Obstacles -----------------
void Stage::createFloor(sf::Vector2f pos) {
    Entities::Floor* pFloor = new Entities::Floor(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize));
    structureList->addEntity(pFloor);
    pCollision->includeEntity(static_cast<Entities::Entity*>(pFloor));
}


void Stage::createPlatform(sf::Vector2f pos) {
    Entities::Obstacles::Platform* pPlat = new Entities::Obstacles::Platform(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize));
    obstacleList->addEntity(pPlat);
    pCollision->includeEntity(static_cast<Entities::Entity*>(pPlat));
}


// ----------------- Projectile -----------------
void Stage::createProjectile(sf::Vector2f size, int ddamage, float speed, float maxrange, sf::Vector2f position, int whoShot, bool useGravity){
    Entities::Projectile* pProjectile = new Entities::Projectile(size, ddamage, speed, maxrange, position, whoShot, useGravity);
    characterList->addEntity(pProjectile);
    pCollision->includeEntity(pProjectile);
}


// ----------------- Enemies -----------------
void Stage::createSkeleton(sf::Vector2f pos) {
    Entities::Characters::Skeleton* pSkeleton = new Entities::Characters::Skeleton(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize), 10);
    characterList->addEntity(pSkeleton);
    pCollision->includeEntity(pSkeleton);
}


void Stage::draw(sf::RenderWindow* window) {
    sf::View currentView = window->getView();

    background2.setPosition(
        currentView.getCenter().x - currentView.getSize().x / 2,
        currentView.getCenter().y - currentView.getSize().y / 2
    );
    background3.setPosition(
        currentView.getCenter().x - currentView.getSize().x / 2,
        currentView.getCenter().y - currentView.getSize().y / 2
    );

    window->draw(background2);
    window->draw(background3);
    window->draw(background);
    characterList->drawAll(window);
    obstacleList->drawAll(window);
    structureList->drawAll(window);

    // desenha a barra de vida
    window->setView(window->getDefaultView());
    if(hpBar1 && pPlayer1 && pPlayer1->getIsAlive()) {
        hpBar1->draw(window);
    }
    if(hpBar2 && pPlayer2 && pPlayer2->getIsAlive()) {
        hpBar2->draw(window);
    }

    window->setView(currentView); // restaura a view do jogo
}


Entities::Characters::Player* Stage::getPlayer1() {
    return pPlayer1;
}


Entities::Characters::Player* Stage::getPlayer2() {
    return pPlayer2;
}


void Stage::execute() {
    // cout << "called the stage execute" << endl;
    
    List::EntityList* chars = characterList;
    for(int i = 0; i < chars->getSize(); i++) {
        if((*chars)[i]->getIsAlive()) {
           (*chars)[i]->execute(); 
        }
    }

    structureList->executeAll();
    obstacleList->executeAll();

    if(hpBar1) {
        hpBar1->update();
    }
    if(hpBar2) {
        hpBar2->update();
    }

    for(int i = chars->getSize() - 1; i  >= 0; i--) {
        Entities::Entity* ent = (*chars)[i];

        if(!ent->getIsAlive()) {
            if(ent->getTypeId() == Entities::IDs::player) {
                // para tela de gameover
                // Managers::StateManager::getStateManager()->addState(6);
                // para dois jogadores não funciona
            } else {
                pCollision->removeEntity(ent);
                chars->removeEntity(i);
                delete ent;
                ent = nullptr;
            }
            
        }

    }

    pCollision->run();

    bool p1Dead = (pPlayer1 && !pPlayer1->getIsAlive());
    bool p2Dead = (pPlayer2 && !pPlayer2->getIsAlive());
    bool p2Exists = (pPlayer2 != nullptr);

    if(!gameOver && p1Dead && (!p2Exists || p2Dead)) {
        gameOver = true;
        Managers::StateManager::getStateManager()->addState(6);
    }
}


// ---------------- Métodos de Salvamento ----------------

void Stage::saveGame() {
    nlohmann::json j;

    if(pPlayer1) {
        j["entities"].push_back(pPlayer1->save());
    }
    if(pPlayer2) {
        j["entities"].push_back(pPlayer2->save());
    }
    
    // salva inimigos e outros da characterList 
    for(int i = 0; i < characterList->getSize(); i++) {
        Entities::Entity* ent = (*characterList)[i];
        
        // evita salvar projéteis ou players novamente
        if(ent->getTypeId() != Entities::IDs::player && ent->getTypeId() != Entities::IDs::projectile) {
            j["entities"].push_back(ent->save());
        }
    }

    // salvar obstaculos
    for(int i = 0; i < obstacleList->getSize(); i++) {
        j["entities"].push_back((*obstacleList)[i]->save());
    }

    // escrever no arquivo 
    std::ofstream o("savegame.json");
    o << std::setw(4) << j << std::endl;
    std::cout << "Game Saved Successfully" << std::endl;
}


void Stage::loadGame() {
    std::ifstream i("savegame.json");
    if(!i.is_open()) {
        std::cout << "WARNING: Savegame not found or error opening." << std::endl;
        return;
    }

    nlohmann::json j;
    i >> j;
    i.close(); 

    // Limpar o mapa atual
    clearEntity();

    nlohmann::json& entitiesList = j["entities"]; 
    for(size_t i = 0; i < entitiesList.size(); i++) {
        nlohmann::json& element = entitiesList[i]; 

        std::string type = element["type"];
        float x = element["x"];
        float y = element["y"];
        
        try {
            if(type == "player") {
                int pid = element["playerId"]; // para saber se é do jogador 1 ou 2 

                // Se os players já existem, apenas atualizar estado
                if(pid == 1 && pPlayer1) {
                    pPlayer1->loadCharacterState(element);
                    pPlayer1->setPos(sf::Vector2f(x, y));
                    if(element.contains("score")) { // para verificar se a pontuação existe antes de carregar
                        pPlayer1->addScore(element["score"]); 
                    }
                } else if (pid == 2 && pPlayer2) {
                    pPlayer2->loadCharacterState(element);
                    pPlayer2->setPos(sf::Vector2f(x, y));
                    if(element.contains("score")) {
                        pPlayer2->addScore(element["score"]);
                    }
                } else {
                    // Se não existem
                    if(pid == 1) { 
                        createPlayer1(sf::Vector2f(x, y)); 
                        pPlayer1->loadCharacterState(element);
                        if(element.contains("score")) { 
                            pPlayer1->addScore(element["score"]); 
                        }
                    }
                    else { 
                        createPlayer2(sf::Vector2f(x, y));
                        pPlayer2->loadCharacterState(element);
                        if(element.contains("score")) {
                            pPlayer2->addScore(element["score"]);
                        }
                    }
                }
            }
            else if(type == "skeleton") {
                Entities::Characters::Skeleton* s = new Entities::Characters::Skeleton(sf::Vector2f(x, y), sf::Vector2f(tileSize, tileSize), 10);
                s->loadCharacterState(element);
                s->setPlayer1(pPlayer1); 
                if(pPlayer2) {
                    s->setPlayer2(pPlayer2);
                }
                characterList->addEntity(s);
                pCollision->includeEntity(s);
            }
            else if(type == "bat") {
                Entities::Characters::Bat* b = new Entities::Characters::Bat(sf::Vector2f(x, y), sf::Vector2f(tileSize, tileSize), 10);
                b->loadCharacterState(element);
                b->setPlayer1(pPlayer1);
                characterList->addEntity(b);
                pCollision->includeEntity(b);
            }
            else if(type == "death") {
                Entities::Characters::Death* d = new Entities::Characters::Death(sf::Vector2f(x, y), sf::Vector2f(tileSize, tileSize), 10);
                d->loadCharacterState(element);
                d->setStage(this); 
                d->setPlayer1(pPlayer1);
                characterList->addEntity(d);
                pCollision->includeEntity(d);
            }
            else if(type == "platform") {
                Entities::Obstacles::Platform* p = new Entities::Obstacles::Platform(sf::Vector2f(x, y), sf::Vector2f(tileSize, tileSize));
                obstacleList->addEntity(p);
                pCollision->includeEntity(p);
            }
            else if(type == "spike") {
                Entities::Obstacles::Spike* s = new Entities::Obstacles::Spike(sf::Vector2f(x, y), sf::Vector2f(tileSize, tileSize));
                obstacleList->addEntity(s);
                pCollision->includeEntity(s);
            }
            else if(type == "mudhand") {
                Entities::Obstacles::MudHand* m = new Entities::Obstacles::MudHand(sf::Vector2f(x, y), sf::Vector2f(tileSize, tileSize));                
                obstacleList->addEntity(m);
                pCollision->includeEntity(m);
            }
        } catch (const std::exception& e) {
            std::cout << "Error loading entity of type: " << type << ": " << e.what() << std::endl;
        }
    }
    
    std::cout << "Game Successfully Loaded!" << std::endl;
}


void Stage::clearEntity() {
    if (characterList) {
        for (int i = characterList->getSize() - 1; i >= 0; i--) {
            Entities::Entity* ent = (*characterList)[i];
            if (ent) {
                // Não é deletado os players aqui pois o loadGame cuida de recriar eles ou atualizar estado
                if (ent->getTypeId() == Entities::IDs::player) {
                    continue; 
                }
                
                pCollision->removeEntity(ent);
                characterList->removeEntity(i);

                delete ent; 
            }
        }
    }

    // Limpa obstáculos
    if (obstacleList) {
        for (int i = obstacleList->getSize() - 1; i >= 0; i--) {
            Entities::Entity* ent = (*obstacleList)[i];
            if (ent) {
                pCollision->removeEntity(ent);
                obstacleList->removeEntity(i);
                delete ent;
            }
        }
    }
}
// -------------------------------------------------------


}
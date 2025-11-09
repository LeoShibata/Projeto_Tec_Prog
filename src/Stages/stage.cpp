#include "Stages/stage.hpp"

using json = nlohmann::json;
using namespace std;

namespace Stages {

Stage::Stage() : 
    Being(sf::Vector2f(0,0)),
    pEvent(Managers::EventManager::getEventManager()),
    pCollision(nullptr),
    characterList(new List::EntityList()),
    obstacleList(new List::EntityList())
{ 
    pCollision = new Managers::CollisionManager();
    
    try {
        createMap("../assets/map1");
    }
    catch(const std::exception& e) {
        std::cout << "ERROR: Failed to load level JSON. " << std::endl;
        std::cout << e.what() << std::endl;
        exit(1);
    }
}

Stage::~Stage() {
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
}

void Stage::createMap(const char* path) {
    ifstream f(path); // get archive
    if(!f.is_open()) {
        std::cout << "ERROR: Could not open map file st " << path << std::endl;
        return;
    }

    json data = json::parse(f); // pass to jason
    f.close();

    json firstLayer = data["layers"][0]["data"]; // get first matrix
    int height = data["layers"][0]["height"];    // get height matrix
    int width = data["layers"][0]["width"];      // get height layers

    float tileSize = 32.f;

    std::vector<std::vector<int>> matrix(height, std::vector<int>(width));
    for(int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrix[i][j] = firstLayer[i * width + j];
        }
    }

    for(int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int tileId = matrix[i][j];

            float x_pos = j * tileSize;
            float y_pos = i * tileSize;

            // factory logic
            switch(tileId) {
                case(1) : {
                    Entities::Characters::Player* pPlayer = new Entities::Characters::Player(sf::Vector2f(x_pos, y_pos), sf::Vector2f(tileSize, tileSize));
                    characterList->addEntity(pPlayer);

                    pCollision->includeEntity(static_cast<Entities::Entity*>(pPlayer));
                    pCollision->setPlayer(pPlayer);

                    pEvent->setPlayer(pPlayer);
                    Entities::Characters::Enemies::setPlayer(pPlayer);
                    break;
                }
                case(166) : {
                    Entities::Obstacles::Platform* pPlat = new Entities::Obstacles::Platform(sf::Vector2f(x_pos, y_pos), sf::Vector2f(tileSize, tileSize));
                    obstacleList->addEntity(pPlat);
                    pCollision->includeEntity(static_cast<Entities::Entity*>(pPlat));
                    break;
                }

                default:
                    break;
            }
        }
    }
}

void Stage::draw(sf::RenderWindow* window) {
    characterList->drawAll(window);
    obstacleList->drawAll(window);
}

void Stage::execute() {
    characterList->executeAll();
    obstacleList->executeAll();
    pCollision->run();
}

}
#include "Stages/Stage1.hpp"

#include "Entities/Characters/Player.hpp"
#include "Entities/Obstacles/Platform.hpp"
#include "Entities/Characters/Enemies/Spirit.hpp"

using json = nlohmann::json;

namespace Stages {

Stage1::Stage1() : 
    Stage() 
{
    try {
        createMap();
    }
    catch (const std::exception& e) {
        std::cout << "ERROR: Failed to load level JSON. " <<  std::endl;
        std::cout << e.what() << std::endl;
        exit(1);
    }
}

Stage1::~Stage1() { }

void Stage1::createMap() {
    const char* path = "../assets/MoonGraveyard";

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
                    pGraphic->setPlayer(pPlayer);
                    break;
                }
                case(3) : {
                    int nivel_maldade = 10;
                    Entities::Characters::Spirit* pSpirit = new Entities::Characters::Spirit(sf::Vector2f(x_pos, y_pos), sf::Vector2f(tileSize, tileSize), nivel_maldade);
                    characterList->addEntity(pSpirit);
                    pCollision->includeEntity(pSpirit);
                    break;
                }
                case(74) : {
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

}
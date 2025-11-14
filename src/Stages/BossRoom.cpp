#include "Stages/BossRoom.hpp"

#include "Entities/Characters/Player.hpp"
#include "Entities/Obstacles/Platform.hpp"
#include "Entities/Characters/Enemies/Bat.hpp"

using json = nlohmann::json;

namespace Stages {

BossRoom::BossRoom() : 
    Stage(), max_boss(0){
    try {
        srand(time(0));
        createMap();
    }
    catch (const std::exception& e) {
        std::cout << "ERROR: Failed to load level JSON. " <<  std::endl;
        std::cout << e.what() << std::endl;
        exit(1);
    }
}

BossRoom::~BossRoom() { }

void BossRoom::createMap() {
    const char* path = "../assets/stages/bossRoom";

    ifstream f(path); // get archive
    if(!f.is_open()) {
        std::cout << "ERROR: Could not open map file st " << path << std::endl;
        return;
    }

    json data = json::parse(f); // pass to jason
    f.close();

    json firstLayer = data["layers"][1]["data"]; // get first matrix
    int height = data["layers"][1]["height"];    // get height matrix
    int width = data["layers"][1]["width"];      // get height layers

    float tileSize = 32.f;
    int qtd=0;
    vector<sf::Vector2f> random_enemies((max_bats)*2); //Random entities vector;

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
                    createPlayer(sf::Vector2(x_pos,y_pos));
                    break;
                }
                case(177) : {
                    random_enemies[qtd] = sf::Vector2f(x_pos, y_pos);
                    cout << random_enemies[qtd].x << " " << random_enemies[qtd].y << endl;
                    qtd++;

                    break;
                }
                case(159) : {
                    createPlatform(sf::Vector2(x_pos,y_pos));
                    break;
                }

                default:
                    break;
            }
        }
    }
    int rangedNumber;
    for (qtd = 0; qtd < random_enemies.size(); qtd++)
    {
        rangedNumber = (rand() % 10) + 1;
        if (rangedNumber>5){
            createBat(random_enemies[qtd]);
        }else{
            // cout << "Nao criou no espaço" << random_enemies[qtd].x << " " << random_enemies[qtd].y << endl;
        }
    }
    

}

}
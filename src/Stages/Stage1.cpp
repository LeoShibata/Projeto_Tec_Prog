#include "Stages/Stage1.hpp"

#include "Entities/Characters/Player.hpp"
#include "Entities/Obstacles/Platform.hpp"
#include "Entities/Characters/Enemies/Spirit.hpp"

using json = nlohmann::json;

namespace Stages {

Stage1::Stage1() : 
    Stage(), max_skeletons(0){
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
    int qtd=0;
    vector<sf::Vector2f> random_enemies((max_skeletons+max_spirits)*2); //Random entities vector;

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
                case(3) : {
                    random_enemies[qtd] = sf::Vector2f(x_pos, y_pos);
                    cout << random_enemies[qtd].x << " " << random_enemies[qtd].y << endl;
                    qtd++;

                    break;
                }
                case(74) : {
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
            createSpirit(random_enemies[qtd]);
        }else{
            cout << "num criou no espaço" << random_enemies[qtd].x << " " << random_enemies[qtd].y << endl;
        }
    }
    

}

}
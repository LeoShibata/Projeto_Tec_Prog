#include "Stages/Graveyard.hpp"

using json = nlohmann::json;


namespace Stages {


Graveyard::Graveyard() : 
    Stage(), 
    max_skeletons(20),
    max_mudhand(20)
{
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


Graveyard::~Graveyard() { }


void Graveyard::createMap() {
    if(!bgTexture.loadFromFile("../assets/stages/Graveyard/MoonGraveyard.png")) {
        std::cout << "ERROR: Failed to load background texture for Graveyard" << std::endl;
        exit(1);
    }   
    background.setTexture(&bgTexture);
    background.setSize(sf::Vector2f(bgTexture.getSize().x, bgTexture.getSize().y));
    background.setPosition(0.f, 0.f);
   
    const char* path = "../assets/stages/Graveyard/MoonGraveyard";
    
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
    int qtd = 0;

    vector<sf::Vector2f> bat_positions; //Random spirits vector;
    vector<sf::Vector2f> skeleton_positions; 
    vector<sf::Vector2f> mudhand_positions; 

    std::vector<std::vector<int>> matrix(height, std::vector<int>(width));
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
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
                    createPlayer1(sf::Vector2(x_pos, y_pos));
                    break;
                }
                case(2) : {
                    createPlayer2(sf::Vector2(x_pos, y_pos));
                    break;
                }
                case(3) : {
                    bat_positions.push_back({x_pos, y_pos});
                    break;
                }
                case(4) : {
                    skeleton_positions.push_back({x_pos, y_pos});
                    break;
                }
                case(5) : {
                    createDeath({x_pos, y_pos});
                    break;
                }
                case(74) : {
                    createPlatform(sf::Vector2(x_pos, y_pos));
                    break;
                }
                case(75) : {
                    createFloor(sf::Vector2(x_pos, y_pos));
                    break;
                }
                case(76) : {
                    mudhand_positions.push_back(sf::Vector2(x_pos, y_pos));
                    break;
                }

                default:
                    break;
            }
        }
    }

    // Create spirits
    int spirits_spawned = 0;
    for (int i = 0; i < bat_positions.size(); i++) {
            if(spirits_spawned < max_bats) {
                if ((rand() % 10) > 4) {// 60% chance
                createBat(bat_positions[i]);
                spirits_spawned++;
            }
        }
    }

    // Create Skeletons
    int skeletons_spawned = 0;
    for (int i = 0; i < skeleton_positions.size(); i++) {
            if(skeletons_spawned < max_skeletons) {
                if ((rand() % 10) > 4) {
                createSkeleton(skeleton_positions[i]);
                skeletons_spawned++;
            }
        }
    }
    
    int mudhand_spawned = 0;
    for (int i = 0; i < mudhand_positions.size(); i++) {
            if(mudhand_spawned < max_mudhand) {
                if ((rand() % 10) > 4) {
                createMudHand(mudhand_positions[i]);
                mudhand_spawned++;
            }
        }
    }
}


}
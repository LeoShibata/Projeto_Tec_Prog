#include "Stages/Graveyard.hpp"
#include "States/StatePlaying.hpp"

using json = nlohmann::json;
using namespace std;

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


void Graveyard::createMudHand(sf::Vector2f pos) {
    Entities::Obstacles::MudHand* pMudHand = new Entities::Obstacles::MudHand(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize));
    obstacleList->addEntity(pMudHand);
    pCollision->includeEntity(static_cast<Entities::Entity*>(pMudHand));
}


void Graveyard::createBat(sf::Vector2f pos) {
    Entities::Characters::Bat* pBat = new Entities::Characters::Bat(sf::Vector2f(pos),sf::Vector2f(tileSize, tileSize), 10);
    characterList->addEntity(pBat);
    pCollision->includeEntity(pBat);
}


void Graveyard::createMap() {
    if(!bgTexture.loadFromFile("../assets/stages/Graveyard/MoonGraveyard.png")) {
        std::cout << "ERROR: Failed to load background texture for Graveyard" << std::endl;
        exit(1);
    }   
    background.setTexture(&bgTexture);
    background.setSize(sf::Vector2f(bgTexture.getSize().x, bgTexture.getSize().y));
    background.setPosition(0.f, 0.f);

    if(!bgTexture2.loadFromFile("../assets/stages/Graveyard/Background_0.png")) {
        std::cout << "ERROR: Failed to load background 2 texture for Graveyard" << std::endl;
        exit(1);
    }
    background2.setTexture(&bgTexture2);
    background2.setSize(sf::Vector2f(bgTexture2.getSize().x, bgTexture2.getSize().y));
    background2.setPosition(0.f, 0.f);
   
    if(!bgTexture3.loadFromFile("../assets/stages/Graveyard/Background_1.png")) {
        std::cout << "ERROR: Failed to load background 3 texture for Graveyard" << std::endl;
        exit(1);
    }
    background3.setTexture(&bgTexture3);
    background3.setSize(sf::Vector2f(bgTexture3.getSize().x, bgTexture3.getSize().y));
    background3.setPosition(0.f, 0.f);

   
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
                    createPlayer1(sf::Vector2f(x_pos, y_pos));
                    break;
                }
                case(2) : {
                    if(States::StatePlaying::playersCount == 2) {
                        createPlayer2(sf::Vector2f(x_pos, y_pos));
                    }
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
                case(74) : {
                    createPlatform(sf::Vector2f(x_pos, y_pos));
                    break;
                }
                case(75) : {
                    createFloor(sf::Vector2f(x_pos, y_pos));
                    break;
                }
                case(76) : {
                    mudhand_positions.push_back(sf::Vector2f(x_pos, y_pos));
                    break;
                }

                default:
                    break;
            }
        }
    }

    // Create bat
    int bat_spawned = 0;
    for (int i = 0; i < bat_positions.size(); i++) {
            if(bat_spawned < max_bats) {
                if ((rand() % 10) > 4) {// 60% chance
                createBat(bat_positions[i]);
                bat_spawned++;
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
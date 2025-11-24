#include "Stages/Castle.hpp"
#include "States/StatePlaying.hpp"


#include "Entities/Characters/Player.hpp"
#include "Entities/Obstacles/Platform.hpp"
#include "Entities/Characters/Enemies/Bat.hpp"

using json = nlohmann::json;
using namespace std;

namespace Stages {

Castle::Castle() : 
    Stage(), 
    max_skeletons(20),
    max_spikes(20)
{
    this->levelId = 2;
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


Castle::~Castle() { }


void Castle::createSpike(sf::Vector2f pos) {
    Entities::Obstacles::Spike* pSpike = new Entities::Obstacles::Spike(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize));
    obstacleList->addEntity(pSpike);
    pCollision->includeEntity(static_cast<Entities::Entity*>(pSpike));
}


void Castle::createDeath(sf::Vector2f pos) {
    Entities::Characters::Death* pDeath = new Entities::Characters::Death(sf::Vector2f(pos), sf::Vector2f(tileSize, tileSize), 10);
    pDeath->setStage(static_cast<Stage*>(this));
    characterList->addEntity(pDeath);
    pCollision->includeEntity(pDeath);
}


void Castle::createMap() {
    if(!bgTexture.loadFromFile("../assets/stages/Castle/Castle.png")) {
        std::cout << "ERROR: Failed to load background texture for Graveyard" << std::endl;
        exit(1);
    }   
    background.setTexture(&bgTexture);
    background.setSize(sf::Vector2f(bgTexture.getSize().x, bgTexture.getSize().y));
    background.setPosition(0.f, 0.f);

    if(!bgTexture2.loadFromFile("../assets/stages/Graveyard/Background_0.png")) {
        std::cout << "ERROR: Failed to load background 3 texture for Graveyard" << std::endl;
        exit(1);
    }
    background2.setTexture(&bgTexture2);
    background2.setSize(sf::Vector2f(bgTexture2.getSize().x, bgTexture2.getSize().y));
    background2.setPosition(0.f, 0.f);

    const char* path = "../assets/stages/Castle/Castle";

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
    vector<sf::Vector2f> spikes_positions; //Random spirits vector;
    vector<sf::Vector2f> skeleton_positions;  //Random entities vector;

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
                    createPlayer1(sf::Vector2(x_pos, y_pos));
                    break;
                }
                case(2) : {
                    if(States::StatePlaying::playersCount == 2) {
                        createPlayer2(sf::Vector2f(x_pos, y_pos));
                    }
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
                    spikes_positions.push_back({x_pos, y_pos});
                    break;
                }
                case(76) : {
                    createFloor(sf::Vector2(x_pos, y_pos));
                    break;
                }

                default:
                    break;
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

    int spikes_spawned = 0;
    for (int i = 0; i < spikes_positions.size(); i++) {
            if(spikes_spawned < max_spikes) {
                if ((rand() % 10) > 4) {
                createSpike(spikes_positions[i]);
                spikes_spawned++;
            }
        }
    }
}

}
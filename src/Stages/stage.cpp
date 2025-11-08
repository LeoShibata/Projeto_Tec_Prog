#include "Stages/stage.hpp"
using namespace std;
using json = nlohmann::json;

namespace Stages{

    Stage::Stage(): Being(sf::Vector2f(0,0)){

    }

    Stage::~Stage(){}
    void Stage::createMap(){
        ifstream f("../assets/map1."); //get archive
        json data = json::parse(f); //pass to jason

        json firstLayer = data["layers"][0]["data"]; //get first matrix
        int height = data["layers"][0]["height"];// get height matrix
        int width = data["layers"][0]["width"];// get height layers

        std::vector<std::vector<int>> matrix(height, std::vector<int>(width));
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                matrix[i][j] = firstLayer[i * width + j];
            }
        }

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                cout << matrix[i][j]<< " " ;
            }
            cout << endl;
        }

    }
    void Stage::execute(){
        cout <<" lmao" <<endl;
    }

}
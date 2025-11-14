#ifndef ANIMATOR
#define ANIMATOR

#include "Image.hpp"
#include <map>

namespace Animation{
    class Animator
    {
    private:
        sf::RectangleShape* body; //get and store size and center reference from characters
        std::map<std::string, Image*> imageMap; //guard the textures, instead of IDS and enum, its map
        sf::Clock clock; //elapsed time for animations
        std::string imageState; //States to change the animations, maybe make a enum
    public:
        Animator(sf::RectangleShape *body);
        ~Animator();
        void update(const bool isRight, std::string imageState); //is const to not change isRight inside this class
        void addAnimation(const char* texturePath, std::string animationName, 
                          const unsigned int imgCounter, const float frameTime, 
                          const sf::Vector2f scale, int rows = 1, int cols = 0);
    };
}
#endif 
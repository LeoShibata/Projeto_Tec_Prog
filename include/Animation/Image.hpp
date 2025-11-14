#ifndef IMAGE
#define IMAGE

#include <SFML/Graphics.hpp>
#include "Managers/GraphicManager.hpp"
//code inspired from gg https://www.youtube.com/watch?v=ssQd0iP0zaI&list=PLR17O9xbTbIBBoL3lli44N8LdZVvg-_uZ&index=8
namespace Animation{
    class Image
    {
    private:
        Managers::GraphicManager* pGraphic; //what will draw
        sf::Texture texture; //texture
        sf::IntRect size;// size
        const sf::Vector2f scale;
        const unsigned int imagecounter; //counter images in line
        unsigned int atualImage; //change between images in line
        const float frameTime; //time to change images
        float animationTime; //time to make full cicle
        int numRows;
        int numCols;
        
        public:
        Image(const char* texturePath, const unsigned int imagecounter, const float frameTime, const sf::Vector2f scale, int rows, int cols);
        ~Image();
        void update(const bool isRight, const float delayTime);//change images
        void reset();//reset circles between states
        const sf::Texture* getTexture();
        const sf::IntRect getSize();
        const sf::Vector2f getScale();

    };
}
#endif
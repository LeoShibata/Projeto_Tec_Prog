#include "Animation/Image.hpp"

using namespace Animation;

Image::Image(const char* texturePath, const unsigned int imagecounter, const float frameTime, const sf::Vector2f scale, int rows, int cols) :
    pGraphic(pGraphic->getGraphicManager()),
    imagecounter(imagecounter),
    frameTime(frameTime),
    animationTime(0.f),
    size(0, 0, 0, 0),
    scale(scale),
    texture(pGraphic->loadFileTexture(texturePath)),
    numRows(rows),
    numCols(cols)
{ 
    if(this->numCols == 0) {
        if(this->numRows == 1) {
            this->numCols = imagecounter; // há apenas uma linha
        } else {
            this->numCols = imagecounter / this->numRows;
        }
    }

    size.width = texture.getSize().x / this->numCols;
    size.height = texture.getSize().y / this->numRows;
}

Image::~Image() { }

void Image::update(const bool isRight, const float delayTime) {
    animationTime = animationTime + delayTime;

    if(animationTime >= frameTime) {
        animationTime -= frameTime;
        atualImage++;
        if(atualImage >= imagecounter) {
            atualImage = 0;
        }
    }

    int row = atualImage / numCols;
    int col = atualImage % numCols;

    size.top = row * abs(size.height);

    if(isRight) {
        size.left = (col + 1) * abs(size.width);
        size.width = -abs(size.width);
    } else {
        size.left =  col * size.width;
        size.width = abs(size.width);
    }
}

void Image::reset() {
    atualImage = 0;
    animationTime = 0;
}

const sf::Texture* Image:: getTexture() {
    return &texture;
}
const sf::IntRect Image::getSize() {
    return size;
}
const sf::Vector2f Image::getScale() {
    return scale;
}
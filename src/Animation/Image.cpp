#include "Animation/Image.hpp"

using namespace Animation;

    Image::Image(const char* texturePath, const unsigned int imagecounter, const float frameTime, const sf::Vector2f scale):
    pGraphic(pGraphic->getGraphicManager()),
    imagecounter(imagecounter),
    frameTime(frameTime),
    animationTime(0.f),
    size(0,0,0,0),
    scale(scale),
    texture(pGraphic->loadFileTexture(texturePath))
    {
        size.width = texture.getSize().x/ (float)imagecounter;
        size.height = texture.getSize().y;
    }

    Image::~Image(){

    }

    void Image::update(const bool isRight, const float delayTime){
        animationTime = animationTime + delayTime;
        if(animationTime >= frameTime){
            animationTime -= frameTime;
            atualImage++;
            if(atualImage >= imagecounter){
            atualImage = 0;
            }
        }
        if(isRight){
            size.left = (atualImage+1) * abs(size.width);
            size.width = -abs(size.width);
        } else {
            size.left =  atualImage * size.width;
            size.width = abs(size.width);
        }
    }

    void Image::reset(){
        atualImage = 0;
        animationTime = 0;
    }

    const sf::Texture* Image:: getTexture(){
        return &texture;
    }
    const sf::IntRect Image::getSize(){
        return size;
    }
    const sf::Vector2f Image::getScale(){
        return scale;
    }
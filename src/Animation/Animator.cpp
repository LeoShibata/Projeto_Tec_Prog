#include "Animation/Animator.hpp"

using namespace Animation;

Animator::Animator(sf::RectangleShape* body): 
    body(body),
    imageMap(),
    imageState(""),
    clock()
{

}

Animator::~Animator(){
    std::map<std::string, Image*>::iterator it;
    for(it = imageMap.begin(); it!= imageMap.end();it++){
        if(it->second){
            delete(it->second); //cleaning texture
            it->second = nullptr; //making the space null. to clear after
        }
    }
    imageMap.clear();
}

void Animator::update(const bool isRight, std::string imageState){
    //class is to update the moments when its change;
    if(this->imageState != imageState){
        if(this->imageState != "")
            imageMap[this->imageState]->reset(); //was image name in add Animation
        this->imageState = imageState;    
    }
    float delayTime = clock.getElapsedTime().asSeconds();
    clock.restart(); //timer that will be up behind the code
    Image *image = imageMap[this->imageState]; //pass the image based on the state, to an aux var
    sf::Vector2f bodySize = body->getSize();
    sf::Vector2f scale = image->getScale(); //connection between image
    
    image->update(isRight, delayTime);
    body->setTextureRect(image->getSize()); //chopping the image
    body->setTexture(image->getTexture());//load texture
    body->setScale(scale.x,scale.y); //dont know what this actually do;
}

void Animator::addAnimation(const char* texturePath, std::string animationName, const unsigned int imgCounter, const float frameTime, const sf::Vector2f scale){
    Image *image = new Image(texturePath, imgCounter, frameTime, scale);
    imageMap.insert(std::pair<std::string, Image*>(animationName, image));
    
}   
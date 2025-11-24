#include "Animation/Animator.hpp"

using namespace Animation;

Animator::Animator(sf::RectangleShape* body) : 
    body(body),
    imageMap(),
    imageState(""),
    clock()
{

}

Animator::~Animator() {
    std::map<std::string, Image*>::iterator it;
    for(it = imageMap.begin(); it!= imageMap.end();it++) {
        if(it->second) {
            delete(it->second); //cleaning texture
            it->second = nullptr; //making the space null. to clear after
        }
    }
    imageMap.clear();
}

void Animator::update(const bool isRight, std::string imageState) {
    //class is to update the moments when its change;
    if(this->imageState != imageState) {
        if(this->imageState != "")
            imageMap[this->imageState]->reset(); //was image name in add Animation
        this->imageState = imageState;    
    }
    float delayTime = clock.getElapsedTime().asSeconds(); 
    clock.restart();

    // --- ADD THIS FIX ---
    // If the time exceeds a safe threshold (e.g., 0.1 seconds), clamp it.
    // This prevents physics from breaking after a pause or lag spike.
    float max_frame_time = 0.1f;
    
    if (delayTime > max_frame_time) {
        delayTime = max_frame_time;
    }
    Image *image = imageMap[this->imageState]; //pass the image based on the state, to an aux var
    sf::Vector2f bodySize = body->getSize();
    sf::Vector2f scale = image->getScale(); //connection between image
    
    image->update(isRight, delayTime);
    body->setTextureRect(image->getSize()); //chopping the image
    body->setTexture(image->getTexture());//load texture
    body->setScale(scale.x,scale.y); //change size of texture;
}

void Animator::addAnimation(const char* texturePath, std::string animationName, const unsigned int imgCounter, 
                            const float frameTime, const sf::Vector2f scale, int rows, int cols) 
{
    Image *image = new Image(texturePath, imgCounter, frameTime, scale, rows, cols);
    imageMap.insert(std::pair<std::string, Image*>(animationName, image));
}   
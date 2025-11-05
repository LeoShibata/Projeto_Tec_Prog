#include "Entities/Characters/Spirit.hpp"
#include <stdio.h>
using namespace std;
namespace Entities::Characters{
    
Spirit::Spirit(const sf::Vector2f position, const sf::Vector2f size, int maldade):    
Enemies(position, size, maldade), soul(0.01f){

    initialize();
    speed_mod = 1.f;
    body.setFillColor(sf::Color::White);
    }
Spirit::~Spirit(){

}
void Spirit::initialize(){}

void Spirit::move(){
    
    body.move(velocity);
}

void Spirit::followPlayer(sf::Vector2f playerPos){
    if (playerPos.x > body.getPosition().x)
        velocity.x = speed_mod*soul;
    else
        velocity.x = -speed_mod*soul;
    if (playerPos.y > body.getPosition().y)
        velocity.y = speed_mod*soul;
    else
        velocity.y = -speed_mod*soul;

    cout << "ta indo" << playerPos.x << endl;
    cout << "ta indo" << velocity.x << endl;
    move();
}

void Spirit::execute(){}

void Spirit::update(){}

void Spirit::collision(Entities::Entity *other){}

}
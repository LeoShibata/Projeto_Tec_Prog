#include "Entities/Characters/Spirit.hpp"
#include <stdio.h>
using namespace std;
namespace Entities::Characters{
    
Spirit::Spirit(const sf::Vector2f position, const sf::Vector2f size, int maldade):    
Enemies(position, size, maldade), soul(0.5f){

    initialize();

    }
Spirit::~Spirit(){

}
void Spirit::initialize(){}

void Spirit::move(){
    body.move(velocity);
}

void Spirit::followPlayer(sf::Vector2f playerPos){
    if (playerPos.x > body.getPosition().x)
        velocity.x = speed_mod;
    else
        velocity.x = -speed_mod;
    if (playerPos.y > body.getPosition().y)
        velocity.y = speed_mod;
    else
        velocity.y = -speed_mod;

    cout << "ta indo" << playerPos.x << endl;
    cout << "ta indo" << velocity.x << endl;
    move();
}

void Spirit::execute(){}

void Spirit::update(){}

void Spirit::collision(Entities::Entity *other){}

}
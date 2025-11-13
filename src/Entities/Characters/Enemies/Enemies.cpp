#include "Entities/Characters/Enemies/Enemies.hpp"
#include "Entities/Characters/Player.hpp"

#include <cmath>

namespace Entities::Characters {

Player* Enemies::pPlayer = nullptr; 

void Enemies::initialize() { }

Enemies::Enemies(const sf::Vector2f position, const sf::Vector2f size, int maldade):    
    Character(position, size, 10.f), 
    nivel_maldade(maldade) 
{
    initialize();
    typeId = IDs::enemy;
}

Enemies::~Enemies() { }

float Enemies::distanceSq(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2);
}

void Enemies::setPlayer(Player* p) {
    pPlayer = p;
}

void Enemies::playerCollide(Player *pPlayer) { }

void Enemies::damaging(Player *pPlayer) { }

}
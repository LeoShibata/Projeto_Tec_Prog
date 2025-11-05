#include "Entities/Characters/Enemies/Enemies.hpp"
#include "Entities/Characters/Player.hpp"

namespace Entities::Characters {

Player* Enemies::pPlayer = nullptr; 

void Enemies::initialize() { }

Enemies::Enemies(const sf::Vector2f position, const sf::Vector2f size, int maldade):    
    Character(position, size, 10.f), 
    nivel_maldade(maldade) 
{
    initialize();
}

Enemies::~Enemies() { }

void Enemies::setPlayer(Player* p) {
    pPlayer = p;
}

void Enemies::playerCollide(Player *pPlayer) { }

void Enemies::damaging(Player *pPlayer) { }

}
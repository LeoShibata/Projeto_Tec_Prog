#include "Entities/Characters/Enemies/Enemies.hpp"

namespace Entities::Characters {
    
Enemies::Enemies(const sf::Vector2f position, const sf::Vector2f size, int maldade):    
    Character(position, size, 10.f), nivel_maldade(maldade) 
{
    initialize();
}

Enemies::~Enemies() { }

void Enemies::initialize() {}

void Enemies::playerCollide(Player *pPlayer) { }

void Enemies::damaging(Player *pPlayer) { }

}
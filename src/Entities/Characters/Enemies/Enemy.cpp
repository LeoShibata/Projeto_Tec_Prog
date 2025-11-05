#include "Entities/Characters/Enemies/Enemy.hpp"

namespace Entities::Characters {

void Enemy::initialize() { }

Enemy::Enemy(const sf::Vector2f position, const sf::Vector2f size, int maldade) :
    Character(position, size, 200), nivel_maldade(maldade)
{
    initialize();
}

Enemy::~Enemy() { }

}
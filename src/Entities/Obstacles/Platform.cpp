#include "Entities/Obstacles/Platform.hpp"

namespace Entities::Obstacles {

Platform::Platform(sf::Vector2f position, sf::Vector2f size) :
    Obstacle(position, size, 0.f)
{
    body.setFillColor(sf::Color::Blue);
}

Platform::~Platform() { }

void Platform::handleCollision(Entities::Characters::Player* pPlayer, sf::Vector2f ds) {

}

}
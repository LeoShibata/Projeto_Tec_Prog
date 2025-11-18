#include "Entities/Obstacles/MudHand.hpp"
#include "Entities/Characters/Player.hpp"

namespace Entities::Obstacles {


void MudHand::initialize() {
    animation.addAnimation("../assets/obstacles/mudhand/spr_enemy_mud_strip8.png", "IDLE", 8, 0.2f, sf::Vector2f(1, 1));
    body.setOrigin(sf::Vector2f(getSize().x/2.f, (getSize().y - 30)/2.f));
}


MudHand::MudHand(sf::Vector2f position, sf::Vector2f size) :
    Obstacle(position, size, 0.f), dt(0.f), animation(&body),
    damageAmount(5), slowDuration(1.5f)
{
    initialize();
    body.setFillColor(sf::Color(199, 145, 112)); // cor marrom
    clock.restart();
}


MudHand::~MudHand() { }


void MudHand::update() {
    dt = clock.getElapsedTime().asSeconds();
    clock.restart();
    animation.update(false, "IDLE");
}


void MudHand::handleCollision(Entities::Characters::Player* pPlayer, float ds, int collisionType) {
    pPlayer->takeDamage(damageAmount);
    pPlayer->applySlow(slowDuration);
}


void MudHand::handleCollision(Entities::Characters::Enemies* pEnemy, float ds, int collisionType) {
    pEnemy->takeDamage(damageAmount);
}


}
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

    damageCooldown = 0.5f;
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

void Enemies::checkPlayerAttack() { 
    // verifica se o inimigo pode tomar dano com o cooldown, se sim, verifica se o jogador tá atacando e se esse ataque o acertou.
    if(pPlayer == nullptr || !pPlayer->getIsAlive()) {
        return;
    }

    if(damageTimer.getElapsedTime().asSeconds() > damageCooldown) {
        if(pPlayer->getIsAttacking()) {
            //medo de por estar fora do gerenciador de colisões o professor n curtir
            sf::FloatRect playerAttackBox = pPlayer->getAttackHitbox();
            sf::FloatRect myHitBox = body.getGlobalBounds(); // caixa exata que inimigo está ocupando na tela
        
            if(playerAttackBox.intersects(myHitBox)) { //verifica se dois retângulos estão se sobrepondo    
                takeDamage(300); // dano que inimigo toma
                damageTimer.restart();
            }
        }
    }
}

}
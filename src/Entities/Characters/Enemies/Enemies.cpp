#include "Entities/Characters/Enemies/Enemies.hpp"
#include "Entities/Characters/Player.hpp"

#include <cmath>

namespace Entities::Characters {


Player* Enemies::pPlayer1 = nullptr;
Player* Enemies::pPlayer2 = nullptr;


void Enemies::initialize() { }


Enemies::Enemies(const sf::Vector2f position, const sf::Vector2f size, int maldade):    
    Character(position, size, 10.f), nivel_maldade(maldade),
    isStunned(false), detectionRadiusSq(250.f * 250.f),
    collisionCooldown(0.f), attackDamage(0)
{
    initialize();
    typeId = IDs::enemy;
    damageCooldown = 0.5f;
    collisionTimer.restart();
}


Enemies::~Enemies() { }


float Enemies::distanceSq(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2);
}


void Enemies::setPlayer1(Player* p) {
    pPlayer1 = p;
}


void Enemies::setPlayer2(Player* p) {
    pPlayer2 = p;
}

void Enemies::clearPlayers() {
    pPlayer1 = nullptr;
    pPlayer2 = nullptr; 
}


void Enemies::playerCollide(Player *pPlayer) { }


void Enemies::damaging(Player *pPlayer) { }


void Enemies::checkPlayerAttack() { 
    // se estiver em cooldown não faz nada
    if(damageTimer.getElapsedTime().asSeconds() <= damageCooldown) {
        return;
    }
    
    // verifica se o inimigo pode tomar dano com o cooldown, se sim, verifica se o jogador tá atacando e se esse ataque o acertou.
    if(pPlayer1 != nullptr && pPlayer1->getIsAlive() && pPlayer1->getIsAttacking()) {
        sf::FloatRect playerAttackBox = pPlayer1->getAttackHitbox();
        sf::FloatRect myHitBox = body.getGlobalBounds();

        if(playerAttackBox.intersects(myHitBox)) {
            takeDamage(90);
            damageTimer.restart();
            return;
        }
    }

    if(pPlayer2 != nullptr && pPlayer2->getIsAlive() && pPlayer2->getIsAttacking()) {
        sf::FloatRect playerAttackBox = pPlayer2->getAttackHitbox();
        sf::FloatRect myHitBox = body.getGlobalBounds();

        if(playerAttackBox.intersects(myHitBox)) {
            takeDamage(100);
            damageTimer.restart();
            return;
        }
    }
}



void Enemies::update() {
    if(isDying) {
        velocity = sf::Vector2f(0.f, 0.f);
        if(dieTimer.getElapsedTime().asSeconds() > dieAnimationDuration) {
            isAlive = false;
        }
        return;
    }

    if(isStunned) {
        if(collisionTimer.getElapsedTime().asSeconds() > collisionCooldown) {
            isStunned = false;
        }
    }

    // Lógica p/ alvo
    Player* pTarget = nullptr;
    float min_dist_sq = detectionRadiusSq; 

    if(pPlayer1 && pPlayer1->getIsAlive()) {
        float dist_sq = distanceSq(body.getPosition(), pPlayer1->getPos());
        if(dist_sq < min_dist_sq) {
            min_dist_sq = dist_sq;
            pTarget = pPlayer1;
        }
    }
    
    if(pPlayer2 && pPlayer2->getIsAlive()) {
        float dist_sq = distanceSq(body.getPosition(), pPlayer2->getPos());
        if(dist_sq < min_dist_sq) {
            min_dist_sq = dist_sq;
            pTarget = pPlayer2;
        }
    }

    if(isAttacking) {   
        velocity.x = 0.f;
        float currentTime = attackTimer.getElapsedTime().asSeconds();

        if(currentTime >= attackDuration) {
            isAttacking = false;
        }

        if(pTarget && pTarget->getIsAlive()) {
            sf::FloatRect myAttackBox = getAttackHitbox();
            sf::FloatRect playerHitbox =pTarget->getBody().getGlobalBounds();

            if(currentTime >= attackDamageStart && currentTime <= attackDamageEnd) {
                if(myAttackBox.intersects(playerHitbox) && !hasAppliedDamage) {
                    pTarget->takeDamage(attackDamage);
                    hasAppliedDamage = true;
                }
            }
        }
    } else {
        performMovement(pTarget, min_dist_sq);
    }

    if(onGround) {
        onGround = false;
    }

    if(velocity.x == 0.f && velocity.y == 0.f) {
        isMoving = false;
    } else {
        isMoving = true;
    }
}

}


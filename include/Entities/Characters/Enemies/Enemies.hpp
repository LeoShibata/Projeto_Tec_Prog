#ifndef ENEMIES_HPP
#define ENEMIES_HPP

#include "Entities/Characters/Character.hpp"
#include "SFML/System/Clock.hpp"

/**
 * USADO TEMPLATE METHOD    
 */

namespace Entities::Characters {
    class Player;
    class Enemies : public Character {
        private:
            int nivel_maldade;

        protected:
            static Player* pPlayer1;
            static Player* pPlayer2;

            bool isStunned;
            float detectionRadiusSq; // raio de detecção e ataque (sobrescrever nos construtures)
            
            sf::Clock collisionTimer;
            float collisionCooldown;

            int attackDamage;
            float attackRangeSq;  
            float attackDamageStart; // Tempo para a hitbox ficar ativa
            float attackDamageEnd;   // Tempo para a hitbox desativar
            bool hasAppliedDamage;


        private:
            void initialize();

        protected:
            void playerCollide(Player* pPlayer);
            
            virtual sf::FloatRect getAttackHitbox() const = 0;
            virtual void attack() = 0;
            virtual void updateAnimation() = 0;
            virtual void performMovement(Player* pTarget, float distance_to_player_sq) = 0; // lógica da IA para movimento (passo variável do template method)

        public:
            Enemies(const sf::Vector2f position, const sf::Vector2f size, int maldade);
            ~Enemies();

            float distanceSq(const sf::Vector2f& v1, const sf::Vector2f& v2);
            static void setPlayer1(Player* p);
            static void setPlayer2(Player* p);
            static void clearPlayers();
            void damaging(Player* pPlayer);
            virtual void checkPlayerAttack();
            
            virtual void update() override;
            
            virtual void move() = 0;
            virtual void execute() = 0;
        };
}

#endif
